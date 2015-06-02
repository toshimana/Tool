#pragma once

#include "ColorTable.h"

class ColorTableColor : public ColorTable
{
public:
	ColorTableColor(void);
	virtual ~ColorTableColor(void);

	void createTable( void );
	std::string getName( void ) const;
};

