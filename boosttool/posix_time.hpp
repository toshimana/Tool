#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/format.hpp>

namespace boosttool
{
	std::string
	getCurrentDateString( const boost::posix_time::ptime& ptime )
	{
		auto date = ptime.date();

		return ( boost::format( "%04d%02d%02d" ) %
			date.year() % static_cast<int>( date.month() ) % date.day()
			).str();
	}

	std::string
	getCurrentDateString( void )
	{
		namespace pt = boost::posix_time;

		pt::ptime ptime = pt::second_clock::local_time();
		return getCurrentDateString( ptime );
	}

	std::string
	getCurrentTimeStringMilliseconds( const boost::posix_time::ptime& ptime )
	{
		auto date = ptime.date();
		auto time = ptime.time_of_day();

		return ( boost::format( "%04d%02d%02d%02d%02d%02d%03d" ) %
			date.year() % static_cast<int>( date.month() ) % date.day() %
			time.hours() % time.minutes() % time.seconds() %
			( time.fractional_seconds()/1000 )  // ミリ秒への変換：マイクロ秒 / 1000
			).str();
	}

	std::string
	getCurrentTimeStringMilliseconds( void )
	{
		namespace pt = boost::posix_time;

		pt::ptime ptime = pt::microsec_clock::local_time();
		return getCurrentTimeStringMilliseconds( ptime );
	}

};