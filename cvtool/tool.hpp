#ifndef   CVTOOL_HPP
#define   CVTOOL_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
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
#endif

namespace cvtool 
{


	//========================================================================
	//	L2点間距離
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
	//	L2点間距離
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
	//	L2点間距離の二乗
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
	//	L2点間距離の二乗
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
	//	有効値かどうかの判定
	//========================================================================
	template< typename T >
	static bool
	isFinite( const cv::Point3_<T>& p )
	{
		return ( _finite( p.x ) && _finite( p.y ) && _finite( p.z ) );
	}

	//========================================================================
	//	点群の平均値を算出
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
	//	差分を算出
	//========================================================================
	template< typename T, int ch >
	static cv::Vec<T,ch>
	sub( cv::Vec<T,ch>& src1, cv::Vec<T,ch>& src2 )
	{
		return src1 - src2;
	}

	//========================================================================
	//	有効値かどうかの判定
	//========================================================================
	template< typename T >
	static bool
	isFinite( const cv::Point_<T>& p )
	{
		return ( _finite( p.x ) && _finite( p.y ) );
	}

	//========================================================================
	//	点が画像領域内に含まれるかの判定
	//========================================================================
	static bool
	contains( cv::InputArray _src, const cv::Point& p )
	{
		const cv::Mat src = _src.getMat();
		cv::Rect region( cv::Point( 0, 0 ), src.size() );
		return region.contains( p );
	}

	//============================================================================
	//  どんな型の値でも取得する
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
	//  cv::Mat::typeを文字列に変換する
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
	//  入力のチャネルを問わないcvtColor
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

	//============================================================================
	//  rvec, tvec の変換方向を逆にする
	//============================================================================
	static void
	InvRT( cv::InputArray  srcRvec, 
		   cv::InputArray  srcTvec, 
		   cv::OutputArray dstRvec, 
		   cv::OutputArray dstTvec )
	{
		dstRvec.getMatRef() = -1 * srcRvec.getMat().clone();

		cv::Mat dstRMat;
		cv::Rodrigues( dstRvec.getMat(), dstRMat );

		dstTvec.getMatRef() = -1 * dstRMat * srcTvec.getMat();
	}

	//============================================================================
	//  3x1回転ベクトルと3x1並進ベクトルから4x4剛体変換行列を算出する
	//============================================================================
	static void
	RT2D( cv::InputArray  rvec,
	      cv::InputArray  tvec,
		  cv::OutputArray DMat )
	{
		cv::Mat dst = cv::Mat::eye( 4, 4, rvec.getMat().depth() );
		cv::Mat RMat;
		cv::Mat rvecMat = rvec.getMat();
		if ( rvecMat.rows == 3 && rvecMat.cols == 3 ) {
			rvecMat.copyTo( RMat );
		} else {
			cv::Rodrigues( rvecMat, RMat );
		}

		RMat         .copyTo( dst( cv::Rect( 0, 0, 3, 3 ) ) );
		tvec.getMat().copyTo( dst( cv::Rect( 3, 0, 1, 3 ) ) );

		DMat.getMatRef() = dst;
	}

	//============================================================================
	//	D行列をR,Tに分解
	//============================================================================
	static void
	D2RT( cv::InputArray  DMat, 
	      cv::OutputArray rvec,
		  cv::OutputArray tvec)
	{
		{
			const cv::Mat DRMat( DMat.getMat(), cv::Rect( 0, 0, 3, 3 ) );
			cv::Mat RMat;
			DRMat.copyTo( RMat );
			cv::Rodrigues( RMat, rvec.getMatRef() );
		}
		{
			const cv::Mat Dtvec( DMat.getMat(), cv::Rect( 3, 0, 1, 3 ) );
			Dtvec.copyTo( tvec.getMatRef() );
		}
	}

	//============================================================================
	//	A,R,TからHomography行列を算出する
	//  Hは3行1列目が1でない値で出力されるので、使用時には注意すること
	//============================================================================
	static void
	ART2H(cv::InputArray cameraMatrix, cv::InputArray rvec, cv::InputArray tvec, cv::OutputArray H)
	{
		cv::Mat preH;
		cv::Rodrigues(rvec.getMat(), preH);
    
		tvec.getMat().copyTo( preH( cv::Rect( 2, 0, 1, 3 ) ) ) ;

		const cv::Mat _H = cameraMatrix.getMat() * preH;
		_H.copyTo( H );    
	}

	//============================================================================
	//	Homography行列とAからR,Tを算出する
	//  参考：https://gist.github.com/inspirit/740979
	//============================================================================
	static void
	HA2RT(cv::InputArray H, cv::InputArray cameraMatrix, cv::OutputArray rvec, cv::OutputArray tvec)
	{
		// Homography行列の作成
		const cv::Mat HMat = H.getMat();
		cv::Mat invCameraMatrix = cameraMatrix.getMat().inv();

		const cv::Mat invH = invCameraMatrix * HMat;

		// ホモグラフィ行列をスケールを調整
		{
			const double lambda = cv::norm( invH.col( 0 ) );
			if ( lambda == 0 ) return;
			const double revLambda = 1.0 / lambda; 
			invCameraMatrix *= revLambda;
		}
		// RMat, tvecの算出
		cv::Mat RMat = invCameraMatrix * HMat;
		const cv::Mat t = RMat.col( 2 ).clone();
		RMat.col( 0 ).cross( RMat.col( 1 ) ).copyTo( RMat.col( 2 ) );

		// SVDでRMatの再調整
		cv::SVD svd( RMat );
		RMat = svd.u * svd.vt;

		cv::Rodrigues( RMat, rvec );
		t.copyTo( tvec );
	}
};

#endif // CVTOOL_HPP