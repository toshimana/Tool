#include "ImageFitWidget.h"

#include <QtDebug>
#include <QMouseEvent>

struct ImageFitWidget::Impl
{
	Impl( ImageFitWidget* obj);
	ImageFitWidget* base;

	boost::signals2::signal<void (const double)>   changedScale;

	QPoint* shiftPrePosition;    //平行移動量計算用の位置
};

ImageFitWidget::Impl::Impl( ImageFitWidget* obj )
	: base( obj )
	, shiftPrePosition( NULL )
{

}

ImageFitWidget::ImageFitWidget( QWidget *pWnd )
	: ImageWidgetBase( pWnd )
	, mImpl( new ImageFitWidget::Impl(this) )
{
	// マウスをクリックしていない時でも
	// mouseMoveEventが反応するように設定する
	setMouseTracking( true );
}

ImageFitWidget::~ImageFitWidget( void )
{
} 

// 以下の値が変更されたときに実行する 
// 1.scaleIndex
// 2.displayImage( displayImage->width(), displayImage->height() )
// 3.表示サイズ( ImageWidget::width(), ImageWidget::height() )
void
ImageFitWidget::createTransformMatrix( void )
{
	QImage displayImage = displayImages[0]->getQImage();

	int imageWidth  = displayImage.width();
	int imageHeight = displayImage.height();
	double scale = std::min( width() / static_cast<double>(imageWidth), height() / static_cast<double>(imageHeight) );

	QTransform trans;
	trans.translate( (width()-scale*imageWidth)/2, (height()-scale*imageHeight)/2 ); // 画像の左上の位置
	trans.scale( scale, scale );
	
	matrix = trans;
	viewport()->update();
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
			matrix.inverted().map( event->x(), event->y(), &postX, &postY );
			changedClickedPointOnImage( QPoint(floor(postX), floor(postY) ) );
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

	if ( !( displayImages[0]->getRawImage().empty() ) ) {
		// 画像上の座標を出力する
		qreal postX, postY;
		matrix.inverted().map( event->x(), event->y(), &postX, &postY );
		changedMouseMovePointOnImage( QPoint( floor( postX ), floor( postY ) ) );
	}
}

