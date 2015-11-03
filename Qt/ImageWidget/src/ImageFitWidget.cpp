#include "ImageFitWidget.h"
#include "QCVImage.h"

#include <boost/signals2/signal.hpp>

#include <QtDebug>
#include <QMouseEvent>

struct ImageFitWidget::Impl
{
	Impl( ImageFitWidget* obj);
	ImageFitWidget* base;

	boost::signals2::signal<void (const QPoint&)>  changedClickedPointOnImage;
	boost::signals2::signal<void (const QPoint&)>  changedMouseMovePointOnImage;
	boost::signals2::signal<void (const double)>   changedScale;
	boost::signals2::signal<void (const cv::Mat&)> changedImage;

	std::vector<SpQCVImage>  displayImages;
	QTransform matrix;
	QPoint* shiftPrePosition;    //平行移動量計算用の位置

	void
	CreateTransformMatrix( void );
};

ImageFitWidget::Impl::Impl( ImageFitWidget* obj )
	: base( obj )
	, shiftPrePosition( NULL )
	, displayImages( 1 )
{

}

// 以下の値が変更されたときに実行する 
// 1.scaleIndex
// 2.displayImage( displayImage->width(), displayImage->height() )
// 3.表示サイズ( ImageWidget::width(), ImageWidget::height() )
void
ImageFitWidget::Impl::CreateTransformMatrix( void )
{
	QImage displayImage = displayImages[0]->getQImage();

	int imageWidth  = displayImage.width();
	int imageHeight = displayImage.height();
	double scale = std::min( base->width() / static_cast<double>(imageWidth), base->height() / static_cast<double>(imageHeight) );

	QTransform trans;
	trans.translate( (base->width()-scale*imageWidth)/2, (base->height()-scale*imageHeight)/2 ); // 画像の左上の位置
	trans.scale( scale, scale );
	
	matrix = trans;
	base->viewport()->update();
}

ImageFitWidget::ImageFitWidget( QWidget *pWnd )
	: QGraphicsView( pWnd )
	, mImpl( new ImageFitWidget::Impl(this) )
{
	// マウスをクリックしていない時でも
	// mouseMoveEventが反応するように設定する
	setMouseTracking( true );
}

ImageFitWidget::~ImageFitWidget( void )
{
} 

void
ImageFitWidget::setImage( cv::InputArray src, const int index )
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
ImageFitWidget::getImage( const int index )
{
	return mImpl->displayImages[index]->getRawImage();
}

void
ImageFitWidget::connectClickedPoint( std::function<void (const QPoint&)> func )
{
	mImpl->changedClickedPointOnImage.connect( func );
}

void
ImageFitWidget::connectChangedMouseMove( std::function<void (const QPoint&)> func )
{
	mImpl->changedMouseMovePointOnImage.connect( func );
}

void
ImageFitWidget::connectChangedImage( std::function<void (const cv::Mat&)> func )
{
	mImpl->changedImage.connect( func );
}

void
ImageFitWidget::paintEvent( QPaintEvent* event )
{
	QPainter widgetpainter( viewport() );
	widgetpainter.setTransform( mImpl->matrix );
	for( int i = 0, n = mImpl->displayImages.size(); i < n; ++i ) {
		widgetpainter.drawImage( 0, 0, mImpl->displayImages[i]->getQImage() );
	}
}

void
ImageFitWidget::resizeEvent( QResizeEvent* event )
{
	if ( !( mImpl->displayImages[0]->getRawImage().empty() ) ) {
		mImpl->CreateTransformMatrix();
	}
}

void
ImageFitWidget::mousePressEvent( QMouseEvent* event )
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
ImageFitWidget::mouseReleaseEvent( QMouseEvent* event )
{
	if ( event->button() == Qt::RightButton ) {
		if ( mImpl->shiftPrePosition != NULL ) delete mImpl->shiftPrePosition;
		mImpl->shiftPrePosition = NULL;
	}

}

void
ImageFitWidget::mouseMoveEvent( QMouseEvent* event )
{

	if ( !(mImpl->displayImages[0]->getRawImage().empty() ) ) {
		// 画像上の座標を出力する
		qreal postX, postY;
		mImpl->matrix.inverted().map( event->x(), event->y(), &postX, &postY );
		mImpl->changedMouseMovePointOnImage( QPoint(floor(postX), floor(postY) ) );
	}
}

