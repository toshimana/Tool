#include "ImageWidgetFit.h"

#include <QMouseEvent>

ImageWidgetFit::ImageWidgetFit( QWidget* parent )
	: ImageWidgetBase( parent )
{
}

ImageWidgetFit::~ImageWidgetFit( void )
{}

void
ImageWidgetFit::createTransformMatrix( void )
{
	QImage displayImage = displayImages[0]->getQImage();

	int imageWidth  = displayImage.width();
	int imageHeight = displayImage.height();
	double wScale =  width() / static_cast<double>(imageWidth);
	double hScale = height() / static_cast<double>(imageHeight);

	QTransform trans;
	trans.translate( (width()-wScale*imageWidth)/2, (height()-hScale*imageHeight)/2 ); // ‰æ‘œ‚Ì¶ã‚ÌˆÊ’u
	trans.scale( wScale, hScale );
	
	matrix = trans;
	viewport()->update();
}
