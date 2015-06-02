#include "ColorTable.h"


ColorTable::ColorTable(void)
{
}


ColorTable::~ColorTable(void)
{
}

void
ColorTable::createTable( void )
{
	for( int i = 0; i < TABLESIZE; ++i ) {
		table[i] = cv::Vec3b( i, i , i );
	}
}



cv::Mat
ColorTable::convert( cv::InputArray _src, double minValue, double maxValue ) const
{
	cv::Mat src;
	_src.getMat().convertTo( src, CV_64FC1 );

	const double df = maxValue - minValue;

	cv::Mat colorImage( src.size(), CV_8UC3 );

	{
		cv::MatConstIterator_<double> sit = src.begin<double>();
		cv::MatIterator_<cv::Vec3b>   dit = colorImage.begin<cv::Vec3b>();
		for( cv::MatConstIterator_<double> endit = src.end<double>(); sit != endit; ++sit, ++dit )
		{
			double base = 255.0 * (*sit - minValue) / df;
			if ( 255.0 < base ) base = 255.0;
			if ( base  < 0.0  ) base = 0.0;
			*dit = table[ static_cast<uchar>( base ) ];
		}
	}

	return colorImage;
}

cv::Mat
	ColorTable::createColorBar( const cv::Size& size, bool vertical ) const
{
	cv::Mat colorBar( size, CV_8UC3 );

	if( vertical ) {
		double weight = static_cast<double>( TABLESIZE ) / static_cast<double>( size.height );

		for( int row = 0; row < size.height; ++row ) {
			int index = cvRound( row * weight );
			cv::Vec3b color = table[index];

			for( int col = 0; col < size.width; ++col ) {
				colorBar.at<cv::Vec3b>( cv::Point( col, row ) ) = color;
			}
		}
		cv::flip( colorBar, colorBar, 0 );

	} else {
		double weight = static_cast<double>( TABLESIZE ) / static_cast<double>( size.width );

		for( int col = 0; col < size.width; ++col ) {
			int index = cvRound( col * weight );
			cv::Vec3b color = table[index];

			for( int row = 0; row < size.height; ++row ) {
				colorBar.at<cv::Vec3b>( cv::Point( col, row ) ) = color;
			}
		}
	}
	return colorBar;
}
