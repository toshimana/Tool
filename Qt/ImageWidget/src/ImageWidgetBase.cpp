#include "ImageWidgetBase.h"

#include <QMouseEvent>

ImageWidgetBase::ImageWidgetBase( QWidget* parent )
	: QGraphicsView( parent )
	, displayImages( 1, QCVImage::create( cv::Mat() ) )
{
	// �}�E�X���N���b�N���Ă��Ȃ����ł�
	// mouseMoveEvent����������悤�ɐݒ肷��
	setMouseTracking( true );

	connect( this, &ImageWidgetBase::pointClickedWithEvent,[this](const cv::Point& p, QMouseEvent* event){
		pointClicked(p);
	});

	connect( this, &ImageWidgetBase::mouseMovedWithEvent, [this](const cv::Point& p, QMouseEvent* event){
		mouseMoved(p);
	});
}

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

	// ���C���摜���X�V���ꂽ�Ȃ�A�ڑ��֐������s����
	if ( index == 0 ) {
		imageChanged( displayImages[index]->getRawImage() );
	}
}

cv::Mat
ImageWidgetBase::getImage( const int index )
{
	return displayImages[index]->getRawImage();
}

void
ImageWidgetBase::clearImage()
{
	displayImages.clear();
	displayImages.resize(1, QCVImage::create(cv::Mat()));

	createTransformMatrix();
}

// �ȉ��̒l���ύX���ꂽ�Ƃ��Ɏ��s���� 
// 1.scaleIndex
// 2.displayImage( displayImage->width(), displayImage->height() )
// 3.�\���T�C�Y( ImageWidget::width(), ImageWidget::height() )
void
ImageWidgetBase::createTransformMatrix( void )
{
	QImage displayImage = displayImages[0]->getQImage();

	int imageWidth  = displayImage.width();
	int imageHeight = displayImage.height();
	double scale = std::min( width() / static_cast<double>(imageWidth), height() / static_cast<double>(imageHeight) );

	QTransform trans;
	trans.translate( (width()-scale*imageWidth)/2, (height()-scale*imageHeight)/2 ); // �摜�̍���̈ʒu
	trans.scale( scale, scale );
	
	matrix = trans;
	viewport()->update();
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
ImageWidgetBase::mousePressEvent( QMouseEvent* event )
{
	cv::Mat rawImage = displayImages[0]->getRawImage();
	if (!(rawImage.empty())) {
		qreal postX, postY;
		matrix.inverted().map(event->x(), event->y(), &postX, &postY);

		cv::Rect region(cv::Point(), rawImage.size());
		cv::Point p(floor(postX), floor(postY));
		if (region.contains(p))	pointClickedWithEvent(p, event);
	}
}

void
ImageWidgetBase::mouseMoveEvent( QMouseEvent* event )
{
	cv::Mat rawImage = displayImages[0]->getRawImage();
	if ( !( rawImage.empty() ) ) {
		// �摜��̍��W���o�͂���
		qreal postX, postY;
		matrix.inverted().map( event->x(), event->y(), &postX, &postY );

		cv::Rect region(cv::Point(), rawImage.size());
		cv::Point p(floor(postX), floor(postY));
		if ( region.contains(p)) mouseMovedWithEvent(p, event);
	}
}

