#pragma once

#define PARAM_GET( type, value, defaultValue ) \
	value = tree.get<type>( section + ( "." # value ), defaultValue ); \
	BOOST_LOG_TRIVIAL( info ) << section << "." #value "=" << value

