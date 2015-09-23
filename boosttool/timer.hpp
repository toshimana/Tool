#pragma once

#include <boost/timer/timer.hpp>

namespace boosttool
{
	struct StopWatch
	{
		std::string tag;
		boost::timer::cpu_timer timer;

		StopWatch( const std::string& _tag ) 
			: tag( _tag )
			, timer()
		{
			std::cout << "BEGIN [" << tag << "]" << std::endl;
		}

		~StopWatch( void ) 
		{
			std::cout << "END   [" << tag << "]" << timer.format() << std::endl;
		}
	};
};