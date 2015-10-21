#pragma once

#include <iostream>
#include <boost/property_tree/ini_parser.hpp>

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
			std::cerr << e.what() << std::endl;
		}
		read( tree );
	}

	void read( const boost::property_tree::ptree& tree )
	{
		std::cout << '[' << section << ']' << std::endl;
		read_impl( tree );
		std::cout << std::endl;
	}

	virtual void read_impl( const boost::property_tree::ptree& tree ) = 0;

	const std::string section;
};
