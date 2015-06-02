#include "ColorTableStepColor.h"

ColorTableStepColor::ColorTableStepColor(void)
	: ColorTable()
{
	createTable();

}


ColorTableStepColor::~ColorTableStepColor(void)
{
}

void
ColorTableStepColor::createTable( void )
{
	const int STEP = 8;
	std::array<cv::Vec3b,STEP> stepColor;

	stepColor[0] = cv::Vec3b( 127,   0,   0 );
	stepColor[1] = cv::Vec3b( 255,   0,   0 );
	stepColor[2] = cv::Vec3b( 255, 127,   0 );
	stepColor[3] = cv::Vec3b( 255, 255,   0 );
	stepColor[4] = cv::Vec3b( 127, 255, 127 );
	stepColor[5] = cv::Vec3b(   0, 255, 255 );
	stepColor[6] = cv::Vec3b(   0, 127, 255 );
	stepColor[7] = cv::Vec3b(   0,   0, 255 );

	const int stepNum = TABLESIZE / STEP;

	for( int i = 0; i < TABLESIZE; ++i ) {
		int sIndex = i / stepNum;
		table[i] = stepColor[sIndex];
	}
	table[TABLESIZE-1] = cv::Vec3b(   0,   0, 127 );
}

std::string
ColorTableStepColor::getName( void ) const
{
	return std::string( "StepColor" );
}
