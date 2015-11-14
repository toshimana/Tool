#pragma once

#define PARAM_GET( type, value ) \
	value = tree.get<type>( section + ( "." # value ), value ); \
	BOOST_LOG_TRIVIAL( info ) << section << "." #value "=" << value

#define PARAM_GET_DEFAULT( type, value, defaultValue ) \
	value = tree.get<type>( section + ( "." # value ), defaultValue ); \
	BOOST_LOG_TRIVIAL( info ) << section << "." #value "=" << value

