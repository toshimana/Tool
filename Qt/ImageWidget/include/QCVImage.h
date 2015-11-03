#pragma once

#include <opencv2/core/core.hpp>
#include <QImage>
#include <memory>

struct QCVImage;
typedef std::shared_ptr<QCVImage> SpQCVImage;

struct QCVImage
{
	~QCVImage( void );

	static SpQCVImage create( cv::InputArray raw );

	cv::Mat getRawImage( void ) const;
	cv::Mat getRGBAImage( void ) const;
	QImage  getQImage( void ) const;

private:
	QCVImage( cv::InputArray raw );

	struct Impl;
	std::unique_ptr<Impl> mImpl;
};