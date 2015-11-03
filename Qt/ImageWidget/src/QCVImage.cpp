#include "QCVImage.h"

#include <opencv2/imgproc/imgproc.hpp>

namespace
{
	void raw2rgba( cv::InputArray src, cv::OutputArray dst )
	{
		switch ( src.channels() ) {
#if OPENCV_VERSION_CODE < OPENCV_VERSION(3,0,0)
		case 1:	cv::cvtColor( src, dst, CV_GRAY2RGBA ); break;
		case 3:	cv::cvtColor( src, dst, CV_BGR2RGBA ); break;
		case 4:	cv::cvtColor( src, dst, CV_BGRA2RGBA ); break;
#else
		case 1:	cv::cvtColor( src, dst, cv::COLOR_GRAY2RGBA ); break;
		case 3:	cv::cvtColor( src, dst, cv::COLOR_BGR2RGBA ); break;
		case 4:	cv::cvtColor( src, dst, cv::COLOR_BGRA2RGBA ); break;
#endif
		default: break;
		}
	}
};

struct QCVImage::Impl
{
	cv::Mat rawImage;
	cv::Mat rgbaImage;
	QImage  qImage;

	Impl( cv::InputArray raw )
		: rawImage( raw.getMat() )
	{
		raw2rgba( raw, rgbaImage );
		qImage = QImage( rgbaImage.ptr(), rgbaImage.cols, rgbaImage.rows, rgbaImage.step, QImage::Format_RGBA8888 );
	}
};

QCVImage::QCVImage( cv::InputArray raw )
	: mImpl( new QCVImage::Impl( raw ) )
{}

QCVImage::~QCVImage( void )
{}

SpQCVImage
QCVImage::create( cv::InputArray raw )
{
	return SpQCVImage( new QCVImage( raw ) );
}


cv::Mat
QCVImage::getRawImage( void ) const
{
	return mImpl->rawImage;
}

cv::Mat
QCVImage::getRGBAImage( void ) const
{
	return mImpl->rgbaImage;
}

QImage
QCVImage::getQImage( void ) const
{
	return mImpl->qImage;
}
