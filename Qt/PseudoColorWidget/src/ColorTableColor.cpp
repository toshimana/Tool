#include "ColorTableColor.h"
#include <opencv2/imgcodecs/imgcodecs.hpp>

ColorTableColor::ColorTableColor(void)
	: ColorTable()
{
	createTable();

	cv::imwrite( "Color1.png", createColorBar( cv::Size( 100, 512 ) ) );
	exit(-1);
}


ColorTableColor::~ColorTableColor(void)
{
}

void
ColorTableColor::createTable( void )
{
	const int STEP = 9;
	std::array<cv::Vec3d,STEP> stepColor;

	stepColor[0] = cv::Vec3d( 127,   0,   0 );
	stepColor[1] = cv::Vec3d( 255,   0,   0 );
	stepColor[2] = cv::Vec3d( 255, 127,   0 );
	stepColor[3] = cv::Vec3d( 255, 255,   0 );
	stepColor[4] = cv::Vec3d( 127, 255, 127 );
	stepColor[5] = cv::Vec3d(   0, 255, 255 );
	stepColor[6] = cv::Vec3d(   0, 127, 255 );
	stepColor[7] = cv::Vec3d(   0,   0, 255 );
	stepColor[8] = cv::Vec3d(   0,   0, 127 );

	const int stepNum = TABLESIZE / ( STEP-1 );
	const double invStepNum = 1.0 / static_cast<double>( stepNum );

	double maxLength = static_cast<double>( TABLESIZE-1 );
	for( int i = 0; i < TABLESIZE; ++i ) {
		int x = i / stepNum;
		int y = x + 1;

		double dfx = ( i - x*stepNum ) * invStepNum;
		double dfy = ( y*stepNum - i ) * invStepNum;

		cv::Vec3d color = ( dfy * stepColor[x] ) + ( dfx * stepColor[y] );
		table[i] = static_cast<cv::Vec3b>( color );
	}
}

std::string
ColorTableColor::getName( void ) const
{
	return std::string( "Color" );
}
