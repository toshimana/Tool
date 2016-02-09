#pragma once

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>

namespace boosttool
{
	template <typename Func>
	class RepeatTimer
	{
	public:
		RepeatTimer( Func _func, const boost::posix_time::time_duration& _time )
			: io()
			, timer( io )
			, func( _func )
			, time( _time )
		{
			setting();
			boost::scoped_ptr<boost::thread> p( new boost::thread( [this](){ io.run(); } ) );
			th.swap( p );
		}

		~RepeatTimer( void )
		{
			io.stop();
			th->join();
		}

		void repeater( void )
		{
			setting();
			func();
		}

		void setting( void )
		{
			timer.expires_from_now( time );
			timer.async_wait( boost::bind( &RepeatTimer::repeater, this ) );
		}


	private:
		boost::asio::io_service io;
		boost::asio::deadline_timer timer;
		Func func;
		const boost::posix_time::time_duration time;
		boost::scoped_ptr<boost::thread> th;
	};
};
