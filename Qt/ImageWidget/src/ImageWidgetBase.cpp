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


