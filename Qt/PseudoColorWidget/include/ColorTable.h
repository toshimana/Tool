#pragma once

#include <opencv2/core/core.hpp>
#include <array>

class ColorTable
{
public:
	ColorTable(void);
	virtual ~ColorTable(void);

	virtual void createTable( void );
	virtual std::string getName( void ) const = 0;

	cv::Mat convert( cv::InputArray src, double minValue, double maxValue ) const;
	cv::Mat createColorBar( const cv::Size& size, bool vertical = true ) const;

protected:
	static const int TABLESIZE = 256;
	std::array<cv::Vec3b, TABLESIZE> table;
};

