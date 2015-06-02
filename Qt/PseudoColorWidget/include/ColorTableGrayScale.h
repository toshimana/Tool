#pragma once

#include "ColorTable.h"

class ColorTableGrayScale : public ColorTable
{
public:
	ColorTableGrayScale(void);
	virtual ~ColorTableGrayScale(void);

	void createTable( void );
	std::string getName( void ) const;
};

