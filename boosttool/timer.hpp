#pragma once

#include <boost/timer/timer.hpp>
#include <boost/log/trivial.hpp>

namespace boosttool
{
	struct StopWatch
	{
		const std::string tag;
		boost::timer::cpu_timer timer;

		StopWatch( const std::string& _tag ) 
			: tag( _tag )
			, timer()
		{
			BOOST_LOG_TRIVIAL( info ) << "BEGIN [" << tag << "]";
		}

		~StopWatch( void ) 
		{
			BOOST_LOG_TRIVIAL( info ) << "END   [" << tag << "]" << timer.format( 6, " %ws wall, %us user + %ss system = %ts CPU (%p%)" );
		}
	};
};