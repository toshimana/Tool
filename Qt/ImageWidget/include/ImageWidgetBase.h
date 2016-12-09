#pragma once

#include <QGraphicsView>
#include "QCVImage.h"

class ImageWidgetBase : public QGraphicsView
{
	Q_OBJECT

public:
	ImageWidgetBase( QWidget* parent = 0 );
	virtual ~ImageWidgetBase( void );

    void 
	setImage( cv::InputArray img, const int index = 0 );

	cv::Mat
	getImage( const int index = 0 );

	void clearImage(void);

signals:
	void imageChanged(cv::Mat);
	void pointClicked(cv::Point);
	void pointClickedWithEvent(cv::Point, QMouseEvent*);
	void mouseMoved(cv::Point);
	void mouseMovedWithEvent(cv::Point, QMouseEvent*);

protected:
	std::vector<SpQCVImage> displayImages;
	QTransform matrix;

	virtual void createTransformMatrix( void );

    void paintEvent( QPaintEvent* event );
	void resizeEvent( QResizeEvent* event );
	virtual void mousePressEvent( QMouseEvent* event );
	virtual void mouseMoveEvent( QMouseEvent* event );
};