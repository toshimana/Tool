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

protected:
	std::vector<SpQCVImage> displayImages;
	QTransform matrix;

	boost::signals2::signal<void(const cv::Mat&)> changedImage;

	virtual void createTransformMatrix( void ) = 0;

    void paintEvent( QPaintEvent* event );
	void resizeEvent( QResizeEvent* event );
};