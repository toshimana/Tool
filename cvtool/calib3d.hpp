#pragma once

#include <opencv2/calib3d/calib3d.hpp>

namespace cvtool 
{
	//============================================================================
	//  rvec, tvec �̕ϊ��������t�ɂ���
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
	//  3x1��]�x�N�g����3x1���i�x�N�g������4x4���̕ϊ��s����Z�o����
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
	//	D�s���R,T�ɕ���
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
	//	A,R,T����Homography�s����Z�o����
	//  H��3�s1��ڂ�1�łȂ��l�ŏo�͂����̂ŁA�g�p���ɂ͒��ӂ��邱��
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
	//	Homography�s���A����R,T���Z�o����
	//  �Q�l�Fhttps://gist.github.com/inspirit/740979
	//============================================================================
	static void
	HA2RT(cv::InputArray H, cv::InputArray cameraMatrix, cv::OutputArray rvec, cv::OutputArray tvec)
	{
		// Homography�s��̍쐬
		const cv::Mat HMat = H.getMat();
		cv::Mat invCameraMatrix = cameraMatrix.getMat().inv();

		const cv::Mat invH = invCameraMatrix * HMat;

		// �z���O���t�B�s����X�P�[���𒲐�
		{
			const double lambda = cv::norm( invH.col( 0 ) );
			if ( lambda == 0 ) return;
			const double revLambda = 1.0 / lambda; 
			invCameraMatrix *= revLambda;
		}
		// RMat, tvec�̎Z�o
		cv::Mat RMat = invCameraMatrix * HMat;
		const cv::Mat t = RMat.col( 2 ).clone();
		RMat.col( 0 ).cross( RMat.col( 1 ) ).copyTo( RMat.col( 2 ) );

		// SVD��RMat�̍Ē���
		cv::SVD svd( RMat );
		RMat = svd.u * svd.vt;

		cv::Rodrigues( RMat, rvec );
		t.copyTo( tvec );
	}
}

