#pragma once

#include "ColorTable.h"

class ColorTableStepColor : public ColorTable
{
public:
	ColorTableStepColor(void);
	virtual ~ColorTableStepColor(void);

	void createTable( void );
	std::string getName( void ) const;
};

