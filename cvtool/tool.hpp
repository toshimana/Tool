#ifndef   CVTOOL_HPP
#define   CVTOOL_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <assert.h>

#define OPENCV_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define OPENCV_VERSION_CODE OPENCV_VERSION(CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION)

#if OPENCV_VERSION_CODE < OPENCV_VERSION(3,0,0)
#define IMREAD_GRAYSCALE CV_LOAD_IMAGE_GRAYSCALE
#define IMREAD_COLOR     CV_LOAD_IMAGE_COLOR
#define COLOR_BGR2GRAY   CV_BGR2GRAY
#else
#define IMREAD_GRAYSCALE cv::IMREAD_GRAYSCALE
#define IMREAD_COLOR     cv::IMREAD_COLOR
#define COLOR_BGR2GRAY   cv::COLOR_BGR2GRAY
#define COLOR_GRAY2BGR   cv::COLOR_GRAY2BGR
#endif

namespace cvtool 
{


	//========================================================================
	//	L2�_�ԋ���
	//========================================================================
	template< typename T >
	static double 
	distance( const cv::Point3_<T>& a, const cv::Point3_<T>& b ) 
	{
		const double dx = a.x - b.x;
		const double dy = a.y - b.y;
		const double dz = a.z - b.z;
		const double squareDistance = dx*dx+dy*dy+dz*dz;
		const double ret = sqrt( squareDistance );
		return ret;
	}

	//========================================================================
	//	L2�_�ԋ���
	//========================================================================
	template< typename T >
	static double 
	distance( const cv::Point_<T>& a, const cv::Point_<T>& b ) 
	{
		const double dx = a.x - b.x;
		const double dy = a.y - b.y;
		const double squareDistance = dx*dx+dy*dy;
		const double ret = sqrt( squareDistance );
		return ret;
	}

	//========================================================================
	//	L2�_�ԋ����̓��
	//========================================================================
	template< typename T >
	static double 
	distanceSquare( const cv::Point3_<T>& a, const cv::Point3_<T>& b ) 
	{
		const double dx = a.x - b.x;
		const double dy = a.y - b.y;
		const double dz = a.z - b.z;
		const double squareDistance = dx*dx+dy*dy+dz*dz;
		return squareDistance;
	}

	//========================================================================
	//	L2�_�ԋ����̓��
	//========================================================================
	template< typename T >
	static double 
	distanceSquare( const cv::Point_<T>& a, const cv::Point_<T>& b ) 
	{
		const double dx = a.x - b.x;
		const double dy = a.y - b.y;
		const double squareDistance = dx*dx+dy*dy;
		return squareDistance;
	}

	//========================================================================
	//	�L���l���ǂ����̔���
	//========================================================================
	template< typename T >
	static bool
	isFinite( const cv::Point3_<T>& p )
	{
		return ( _finite( p.x ) && _finite( p.y ) && _finite( p.z ) );
	}

	//========================================================================
	//	�_�Q�̕��ϒl���Z�o
	//========================================================================
	template< typename T, int ch >
	static cv::Vec<T,ch>
	ave( cv::InputArray src )
	{
		cv::Mat points = src.getMat().reshape( ch, 1 );
		cv::Vec<T,ch> sum;
		for( int i = 0; i < points.cols; ++i ) sum += points.at<cv::Vec<T,ch> >( i );
		return sum / points.cols;
	}

	//========================================================================
	//	�������Z�o
	//========================================================================
	template< typename T, int ch >
	static cv::Vec<T,ch>
	sub( cv::Vec<T,ch>& src1, cv::Vec<T,ch>& src2 )
	{
		return src1 - src2;
	}

	//========================================================================
	//	�L���l���ǂ����̔���
	//========================================================================
	template< typename T >
	static bool
	isFinite( const cv::Point_<T>& p )
	{
		return ( _finite( p.x ) && _finite( p.y ) );
	}

	//========================================================================
	//	�_���摜�̈���Ɋ܂܂�邩�̔���
	//========================================================================
	static bool
	contains( cv::InputArray _src, const cv::Point& p )
	{
		const cv::Mat src = _src.getMat();
		cv::Rect region( cv::Point( 0, 0 ), src.size() );
		return region.contains( p );
	}

	//============================================================================
	//  �ǂ�Ȍ^�̒l�ł��擾����
	//============================================================================
	static double getValue( cv::InputArray _src, const cv::Point& p )
	{
		const cv::Mat src = _src.getMat();
		double value = std::numeric_limits<double>::max();
		const int depth = src.depth();
		switch( depth ) {
		case CV_8U : value = src.at<uchar>         ( p ); break;
		case CV_8S : value = src.at<char>          ( p ); break;
		case CV_16U: value = src.at<unsigned short>( p ); break;
		case CV_16S: value = src.at<short>         ( p ); break;
		case CV_32S: value = src.at<long>          ( p ); break;
		case CV_32F: value = src.at<float>         ( p ); break;
		case CV_64F: value = src.at<double>        ( p ); break;
		}
		return value;
	}

	//============================================================================
	//  cv::Mat::type�𕶎���ɕϊ�����
	// http://stackoverflow.com/questions/10167534/how-to-find-out-what-type-of-a-mat-object-is-with-mattype-in-opencv
	//============================================================================
	std::string type2str(int type) {
		std::string r;

		unsigned char depth = type & CV_MAT_DEPTH_MASK;
		unsigned char chans = 1 + (type >> CV_CN_SHIFT);

		switch ( depth ) {
		case CV_8U:  r = "8U"; break;
		case CV_8S:  r = "8S"; break;
		case CV_16U: r = "16U"; break;
		case CV_16S: r = "16S"; break;
		case CV_32S: r = "32S"; break;
		case CV_32F: r = "32F"; break;
		case CV_64F: r = "64F"; break;
		default:     r = "User"; break;
		}

		r += "C";
		r += (chans+'0');

		return r;
	}

	//============================================================================
	//  ���͂̃`���l������Ȃ�cvtColor
	//============================================================================
	static void
	convertColor( cv::InputArray src, cv::OutputArray dst )
	{
		switch ( src.type() ) {
		case CV_8UC3: src.getMat().copyTo( dst ); break;
		case CV_8UC1: cvtColor( src, dst, COLOR_GRAY2BGR ); break;
		default     : assert( false );
		}
	}

	//============================================================================
	//  ���͂̃`���l������Ȃ�cvtColor
	//============================================================================
	static void
	cvtColor2Gray( cv::InputArray src, cv::OutputArray dst )
	{
		switch ( src.type() ) {
		case CV_8UC3: cv::cvtColor( src, dst, COLOR_BGR2GRAY ); break;
		case CV_8UC1: src.getMat().copyTo( dst );               break;
		default     : assert( false );
		}
	}
};

#endif // CVTOOL_HPP