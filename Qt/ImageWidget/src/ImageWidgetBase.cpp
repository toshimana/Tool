#include "ImageWidgetBase.h"

#include <QMouseEvent>

ImageWidgetBase::ImageWidgetBase( QWidget* parent )
	: QGraphicsView( parent )
	, displayImages( 1 )
{
	// �}�E�X���N���b�N���Ă��Ȃ����ł�
	// mouseMoveEvent����������悤�ɐݒ肷��
	setMouseTracking( true );
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
		changedImage( displayImages[index]->getRawImage() );
	}
}

cv::Mat
ImageWidgetBase::getImage( const int index )
{
	return displayImages[index]->getRawImage();
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

void
ImageWidgetBase::mousePressEvent( QMouseEvent* event )
{
	switch ( event->button() ) {
	case Qt::LeftButton:
		{
			qreal postX, postY;
			matrix.inverted().map( event->x(), event->y(), &postX, &postY );
			changedClickedPointOnImage( QPoint( floor( postX ), floor( postY ) ) );
		} break;
	}
}

void
ImageWidgetBase::mouseMoveEvent( QMouseEvent* event )
{
	if ( !( displayImages[0]->getRawImage().empty() ) ) {
		// �摜��̍��W���o�͂���
		qreal postX, postY;
		matrix.inverted().map( event->x(), event->y(), &postX, &postY );
		changedMouseMovePointOnImage( QPoint( floor( postX ), floor( postY ) ) );
	}
}

