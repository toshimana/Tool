#pragma once

#include "ImageWidgetBase.h"

class ImageWidgetFit : public ImageWidgetBase
{
public:
	ImageWidgetFit( QWidget* parent = 0 );
	virtual ~ImageWidgetFit( void );

protected:
	virtual void createTransformMatrix( void );
};