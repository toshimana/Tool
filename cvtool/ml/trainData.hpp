#pragma once

namespace cvtool
{
	bool saveToCSV( const cv::Ptr<cv::ml::TrainData>& trainData, const std::string& path )
	{
		int trainDataSize = trainData->getNSamples();
		const cv::Mat samples = trainData->getSamples();
		const cv::Mat responses = trainData->getResponses();

		std::stringstream ss;
		for( int row = 0; row < trainDataSize; ++row ) {
			cv::Mat sample = samples.row( row );
			for( auto it = sample.begin<float>(); it != sample.end<float>(); ++it ) {
				ss << *it << ',';
			}
			ss << responses.at<int>( row ) << std::endl;
		}

		std::ofstream ofs( path );
		ofs << ss.str();

		return true;
	}
};