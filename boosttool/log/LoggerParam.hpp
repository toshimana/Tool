#pragma once

#include <boosttool/property_tree/IniParserHelper.hpp>
#include <boosttool/property_tree/IniParserHelperMacro.h>

class LoggerParam : public IniParserHelper
{
public:
	LoggerParam( void ) 
		: IniParserHelper( "Logger" )
		, severity_level( 0 )
	{}

	void read_impl( const boost::property_tree::ptree& tree )
	{
		PARAM_GET( int, severity_level, 0 );
	}

	int severity_level;
};