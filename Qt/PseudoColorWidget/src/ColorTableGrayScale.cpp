#include "ColorTableGrayScale.h"


ColorTableGrayScale::ColorTableGrayScale(void)
	: ColorTable()
{
	createTable();
}


ColorTableGrayScale::~ColorTableGrayScale(void)
{
}

void
ColorTableGrayScale::createTable( void )
{
	for( int i = 0; i < TABLESIZE; ++i ) {
		table[i] = cv::Vec3b( i, i , i );
	}
}

std::string
ColorTableGrayScale::getName( void ) const
{
	return std::string( "GrayScale" );
}
