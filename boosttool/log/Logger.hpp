#pragma once

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

#include "LoggerParam.hpp"

namespace boosttool
{
	class Logger
	{
	public:
		Logger( const std::string& _appName = "SYSTEM" )
			: appName( _appName )
		{
			namespace logging = boost::log;
			namespace sinks = boost::log::sinks;
			namespace expr = boost::log::expressions;
			namespace keywords = boost::log::keywords;

			logging::add_common_attributes();

			logging::add_file_log(
				keywords::auto_flush = true,
				keywords::open_mode = std::ios::app,
				keywords::file_name = "%Y%m%d_%5N.log",
				keywords::target = "log",
				keywords::time_based_rotation = sinks::file::rotation_at_time_point( 0, 0, 0 ),
				keywords::max_size = 10 * 1024 * 1024,
				keywords::format = expr::format("[%1%][%2%][%3%]%4%")
				% expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
				% expr::attr<logging::attributes::current_thread_id::value_type>("ThreadID")
				% logging::trivial::severity
				% expr::message);

			BOOST_LOG_TRIVIAL( info ) << "------------ START " << appName << " ------------";
		}

		~Logger()
		{
			BOOST_LOG_TRIVIAL( info ) << "------------ END   " << appName << " ------------";
		}

		void initialize( const std::string& path, boost::property_tree::ptree& tree )
		{
			LoggerParam param;
			param.read( path, tree );

			// Filter‚ÌÝ’è
			boost::log::core::get()->set_filter( boost::log::trivial::severity >= param.severity_level );
		}

	private:
		const std::string appName;
	};
}