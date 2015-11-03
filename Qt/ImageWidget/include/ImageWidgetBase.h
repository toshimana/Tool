#pragma once

#include <QGraphicsView>
#include "QCVImage.h"

#include <boost/signals2/signal.hpp>


class ImageWidgetBase : public QGraphicsView
{
public:
	ImageWidgetBase( QWidget* parent = 0 );
	virtual ~ImageWidgetBase( void );

    void 
	setImage( cv::InputArray img, const int index = 0 );

	cv::Mat
	getImage( const int index = 0 );

	void
	connectChangedImage( std::function<void (const cv::Mat&)> func );

	void
	connectClickedPoint( std::function<void (const QPoint&)> func );

	void
	connectChangedMouseMove( std::function<void (const QPoint&)> func );

protected:
	std::vector<SpQCVImage> displayImages;
	QTransform matrix;

	boost::signals2::signal<void(const cv::Mat&)> changedImage;
	boost::signals2::signal<void(const QPoint&)>  changedClickedPointOnImage;
	boost::signals2::signal<void(const QPoint&)>  changedMouseMovePointOnImage;

	virtual void createTransformMatrix( void ) = 0;

    void paintEvent( QPaintEvent* event );
	void resizeEvent( QResizeEvent* event );
};