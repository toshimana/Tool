#include "ImageFitWidget.h"

#include <QtDebug>
#include <QMouseEvent>

struct ImageFitWidget::Impl
{
	Impl( ImageFitWidget* obj);
	ImageFitWidget* base;

	boost::signals2::signal<void (const double)>   changedScale;

	QPoint* shiftPrePosition;    //���s�ړ��ʌv�Z�p�̈ʒu
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
	// �}�E�X���N���b�N���Ă��Ȃ����ł�
	// mouseMoveEvent����������悤�ɐݒ肷��
	setMouseTracking( true );
}

ImageFitWidget::~ImageFitWidget( void )
{
} 

// �ȉ��̒l���ύX���ꂽ�Ƃ��Ɏ��s���� 
// 1.scaleIndex
// 2.displayImage( displayImage->width(), displayImage->height() )
// 3.�\���T�C�Y( ImageWidget::width(), ImageWidget::height() )
void
ImageFitWidget::createTransformMatrix( void )
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
		// �摜��̍��W���o�͂���
		qreal postX, postY;
		matrix.inverted().map( event->x(), event->y(), &postX, &postY );
		changedMouseMovePointOnImage( QPoint( floor( postX ), floor( postY ) ) );
	}
}

