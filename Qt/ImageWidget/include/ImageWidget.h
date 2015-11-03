#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "ImageWidgetBase.h"
#include <opencv2/core/core.hpp>
#include <functional>

class ImageWidget : public ImageWidgetBase
{
    Q_OBJECT
public:
    ImageWidget( QWidget* pWnd );
	virtual ~ImageWidget( void );

	void
	setScaleIndex( const int index = -1);

	double
	getScale( void ) const;

	void
	connectChangedScale( std::function<void (const double)> func );

signals:

public slots:

protected:
	void createTransformMatrix( void );

	void mousePressEvent( QMouseEvent* event );
	void mouseReleaseEvent( QMouseEvent* event );
	void mouseMoveEvent( QMouseEvent* event );
	void wheelEvent( QWheelEvent* event );

private:

	class Impl;
	Impl* mImpl;
};

#endif // IMAGEWIDGET_H