#ifndef IMAGEFITWIDGET_H
#define IMAGEFITWIDGET_H

#include "ImageWidgetBase.h"
#include <opencv2/core/core.hpp>
#include <functional>
#include <memory>

class ImageFitWidget : public ImageWidgetBase
{
    Q_OBJECT
public:
    ImageFitWidget( QWidget* pWnd );
	virtual ~ImageFitWidget( void );

	void
	connectClickedPoint( std::function<void (const QPoint&)> func );

	void
	connectChangedMouseMove( std::function<void (const QPoint&)> func );

	void
	connectChangedImage( std::function<void (const cv::Mat&)> func );

signals:

public slots:

protected:
	void createTransformMatrix( void );

	void mousePressEvent( QMouseEvent* event );
	void mouseReleaseEvent( QMouseEvent* event );
	void mouseMoveEvent( QMouseEvent* event );

private:

	struct Impl;
	std::unique_ptr<Impl> mImpl;
};

#endif // IMAGEFITWIDGET_H