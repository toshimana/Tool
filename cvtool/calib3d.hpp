#pragma once

#include <opencv2/calib3d/calib3d.hpp>

namespace cvtool 
{
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
}

