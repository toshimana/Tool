#include "ImageWidget.h"
#include "QCVImage.h"

#include <boost/signals2/signal.hpp>

#include <QtDebug>
#include <QMouseEvent>
#include <array>

namespace
{
	const int NUM_SCALETABLE = 16;
	const int DEFAULT_SCALETABLE_INDEX = 4;
	std::array<double, NUM_SCALETABLE> scaleTable =
	{
		0.10,
		0.25,
		0.50,
		0.75,
		1.00,
		1.50,
		2.00,
		3.00,
		4.00,
		6.00,
		8.00,
		10.00,
		12.00,
		16.00,
		20.00,
		24.00,
	};
}

struct ImageWidget::Impl
{
	Impl( ImageWidget* obj);
	ImageWidget* base;

	boost::signals2::signal<void (const QPoint&)>  changedClickedPointOnImage;
	boost::signals2::signal<void (const QPoint&)>  changedMouseMovePointOnImage;
	boost::signals2::signal<void (const double)>   changedScale;
	boost::signals2::signal<void (const cv::Mat&)> changedImage;

	std::vector<SpQCVImage> displayImages;
	QTransform matrix;
	int     scaleIndex;          //拡大率テーブルのインデックス
	QPointF scaleChangePosition; //拡大・縮小時の中心位置
	QPoint* shiftPrePosition;    //平行移動量計算用の位置

	void
	CreateTransformMatrix( const QPointF& shift = QPointF(0.0,0.0) );
};

ImageWidget::Impl::Impl( ImageWidget* obj )
	: base( obj )
	, scaleIndex( DEFAULT_SCALETABLE_INDEX )
	, scaleChangePosition( 0.0, 0.0 )
	, shiftPrePosition( NULL )
	, displayImages( 1 )
{

}

// 以下の値が変更されたときに実行する 
// 1.scaleIndex
// 2.displayImage( displayImage->width(), displayImage->height() )
// 3.表示サイズ( ImageWidget::width(), ImageWidget::height() )
void
ImageWidget::Impl::CreateTransformMatrix( const QPointF& shift )
{
	const int w = base->width();
	const int h = base->height();

	const QPointF baseP = matrix.inverted().map( scaleChangePosition );
	double aScale = 1.0;
	const double scale = scaleTable[scaleIndex];

	QImage displayImage = displayImages[0]->getQImage();

	const double wOffset = std::max( 0.0, (double)(w - scale*aScale*displayImage.width() )/2 );
	const double hOffset = std::max( 0.0, (double)(h - scale*aScale*displayImage.height())/2 );

	QTransform trans;
	trans.translate( scaleChangePosition.x()-baseP.x()*scale*aScale + shift.x(), 
		             scaleChangePosition.y()-baseP.y()*scale*aScale + shift.y());
	trans.scale( scale,  scale );
	trans.scale( aScale, aScale );
	// 画面内に空白を作らないように、表示位置を調整する
	{
		qreal left, top, right, bottom;
		trans.map( 0.0, 0.0, &left, &top );
		trans.map( displayImage.width(), displayImage.height(), &right, &bottom );
		if ( 0.0                  < left-floor(wOffset) ) trans.translate( (floor(wOffset)-left)/(scale*aScale),   0.0                                     );
		if ( 0.0                  < top -floor(hOffset) ) trans.translate( 0.0,                                    (floor(hOffset)-top)/(scale*aScale)     );
		if ( right +ceil(wOffset) < w                   ) trans.translate( (w-right-ceil(wOffset))/(scale*aScale), 0.0                                     );
		if ( bottom+ceil(hOffset) < h                   ) trans.translate( 0.0,                                    (h-bottom-ceil(hOffset))/(scale*aScale) );
	}

	matrix = trans;
	base->viewport()->update();
}

ImageWidget::ImageWidget( QWidget *pWnd )
	: QGraphicsView( pWnd )
	, mImpl( new ImageWidget::Impl(this) )
{
	// マウスをクリックしていない時でも
	// mouseMoveEventが反応するように設定する
	setMouseTracking( true );
}

ImageWidget::~ImageWidget( void )
{
	delete mImpl;
} 

void
ImageWidget::setImage( cv::InputArray src, const int index )
{
	if ( mImpl->displayImages.size() <= index ) {
		mImpl->displayImages.resize( index + 1 );
	}

	mImpl->displayImages[index] = QCVImage::create( src );

	mImpl->CreateTransformMatrix();

	// メイン画像が更新されたなら、接続関数を実行する
	if ( index == 0 ) {
		mImpl->changedImage( mImpl->displayImages[index]->getRawImage() );
	}
}

cv::Mat
ImageWidget::getImage( const int index )
{
	return mImpl->displayImages[index]->getRawImage();
}

void
ImageWidget::setScaleIndex( const int index )
{
	if ( index < 0 || ( NUM_SCALETABLE-1 < index ) ) {
		mImpl->scaleIndex = DEFAULT_SCALETABLE_INDEX;
	} else {
		mImpl->scaleIndex = index;
	}
	mImpl->changedScale( scaleTable[mImpl->scaleIndex] );
	mImpl->CreateTransformMatrix();
}

double
ImageWidget::getScale( void ) const
{
	return scaleTable[mImpl->scaleIndex];
}

void
ImageWidget::connectClickedPoint( std::function<void (const QPoint&)> func )
{
	mImpl->changedClickedPointOnImage.connect( func );
}

void
ImageWidget::connectChangedMouseMove( std::function<void (const QPoint&)> func )
{
	mImpl->changedMouseMovePointOnImage.connect( func );
}

void
ImageWidget::connectChangedScale( std::function<void (const double)> func )
{
	mImpl->changedScale.connect( func );
}

void
ImageWidget::connectChangedImage( std::function<void (const cv::Mat&)> func )
{
	mImpl->changedImage.connect( func );
}

void
ImageWidget::paintEvent( QPaintEvent* event )
{
	QPainter widgetpainter( viewport() );
	widgetpainter.setTransform( mImpl->matrix );
	for( int i = 0, n = mImpl->displayImages.size(); i < n; ++i ) {
		widgetpainter.drawImage( 0, 0, mImpl->displayImages[i]->getQImage() );
	}
}

void
ImageWidget::resizeEvent( QResizeEvent* event )
{
	if ( !( mImpl->displayImages[0]->getRawImage().empty() ) ) {
		mImpl->CreateTransformMatrix();
	}
}

void
ImageWidget::mousePressEvent( QMouseEvent* event )
{
	switch ( event->button() ) {
	case Qt::RightButton: 
		{
			if ( mImpl->shiftPrePosition != NULL ) delete mImpl->shiftPrePosition;
			mImpl->shiftPrePosition = new QPoint( event->pos() );
		} break;
	case Qt::LeftButton:
		{
			qreal postX, postY;
			mImpl->matrix.inverted().map( event->x(), event->y(), &postX, &postY );
			mImpl->changedClickedPointOnImage( QPoint(floor(postX), floor(postY) ) );
		} break;
	}
}

void 
ImageWidget::mouseReleaseEvent( QMouseEvent* event )
{
	if ( event->button() == Qt::RightButton ) {
		if ( mImpl->shiftPrePosition != NULL ) delete mImpl->shiftPrePosition;
		mImpl->shiftPrePosition = NULL;
	}

}

void
ImageWidget::mouseMoveEvent( QMouseEvent* event )
{

	if ( !( mImpl->displayImages[0]->getRawImage().empty() ) ) {
		// 平行移動計算を実施する
		if ( mImpl->shiftPrePosition != NULL ) {
			const QPointF diff = event->pos() - *(mImpl->shiftPrePosition);
			mImpl->CreateTransformMatrix(diff);

			*(mImpl->shiftPrePosition) = event->pos();
		}

		// 画像上の座標を出力する
		qreal postX, postY;
		mImpl->matrix.inverted().map( event->x(), event->y(), &postX, &postY );
		mImpl->changedMouseMovePointOnImage( QPoint(floor(postX), floor(postY) ) );
	}
}

void
ImageWidget::wheelEvent( QWheelEvent* event )
{
	double sIdx = mImpl->scaleIndex + static_cast<double>(event->delta())/120.0;
	if ( sIdx             < 0    ) sIdx = 0;
	if ( NUM_SCALETABLE-1 < sIdx ) sIdx = NUM_SCALETABLE-1;

	mImpl->scaleChangePosition = event->posF();

	setScaleIndex( sIdx );
}