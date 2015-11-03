#include "ImageWidgetBase.h"

ImageWidgetBase::ImageWidgetBase( QWidget* parent )
	: QGraphicsView( parent )
	, displayImages( 1 )
{}

ImageWidgetBase::~ImageWidgetBase( void )
{}

void
ImageWidgetBase::setImage( cv::InputArray src, const int index )
{
	if ( displayImages.size() <= index ) {
		displayImages.resize( index + 1 );
	}

	displayImages[index] = QCVImage::create( src );

	createTransformMatrix();

	// メイン画像が更新されたなら、接続関数を実行する
	if ( index == 0 ) {
		changedImage( displayImages[index]->getRawImage() );
	}
}

cv::Mat
ImageWidgetBase::getImage( const int index )
{
	return displayImages[index]->getRawImage();
}

void
ImageWidgetBase::paintEvent( QPaintEvent* event )
{
	QPainter widgetpainter( viewport() );
	widgetpainter.setTransform( matrix );
	for( int i = 0, n = displayImages.size(); i < n; ++i ) {
		widgetpainter.drawImage( 0, 0, displayImages[i]->getQImage() );
	}
}

void
ImageWidgetBase::resizeEvent( QResizeEvent* event )
{
	if ( !( displayImages[0]->getRawImage().empty() ) ) {
		createTransformMatrix();
	}
}

void
ImageWidgetBase::connectClickedPoint( std::function<void (const QPoint&)> func )
{
	changedClickedPointOnImage.connect( func );
}

void
ImageWidgetBase::connectChangedMouseMove( std::function<void (const QPoint&)> func )
{
	changedMouseMovePointOnImage.connect( func );
}

void
ImageWidgetBase::connectChangedImage( std::function<void (const cv::Mat&)> func )
{
	changedImage.connect( func );
}

