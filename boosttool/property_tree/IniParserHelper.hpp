#pragma once

#include <boost/property_tree/ini_parser.hpp>
#include <boost/log/trivial.hpp>

class IniParserHelper
{
public:
	IniParserHelper( const std::string& _section )
		: section( _section )
	{}

	virtual ~IniParserHelper() {}

	void read( const std::string& path )
	{
		boost::property_tree::ptree tree;
		read( path, tree );
	}

	void read( const std::string& path, boost::property_tree::ptree& tree )
	{
		try {
			boost::property_tree::read_ini( path, tree );
		}
		catch ( std::exception& e )
		{
			BOOST_LOG_TRIVIAL( warning ) << e.what();
		}
		read( tree );
	}

	void read( const boost::property_tree::ptree& tree )
	{
		read_impl( tree );
	}

	virtual void read_impl( const boost::property_tree::ptree& tree ) = 0;

	const std::string section;
};
