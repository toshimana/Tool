#pragma once

#include <boost/log/trivial.hpp>
#include <boost/format.hpp>

#define ERROR_LOG( ... ) BOOST_LOG_TRIVIAL( error ) << ' ' << __FILE__ << '(' << __LINE__ << ')' << __FUNCTION__ << __VA_ARGS__

#define ERROR_READ( file )  ERROR_LOG( ( boost::format( "fail to read : %s" ) % file ).str() )
#define ERROR_PARSE( file ) ERROR_LOG( ( boost::format( "fail to parse : %s" ) % file ).str() )
#define ERROR_INITIALIZE( device ) ERROR_LOG( ( boost::format( "fail to initialize : %s" ) % device ).str() )
