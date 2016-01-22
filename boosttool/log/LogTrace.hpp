#pragma once

#include <stdio.h>

#include <string>
#include <sstream>
#include <boost/log/trivial.hpp>
#include "../../stltool/ostream.hpp"

namespace {

	// vectorの自動出力用
	using namespace stltool;
	
	// 可変長引数を文字列に変換するクラス
	std::string LogTraceString( void ){ return ""; }
	
	template <typename Arg1>
	std::string LogTraceString( const Arg1& arg1 ){ std::stringstream ss; ss << ',' << arg1; return ss.str(); }

	template <typename Arg1,typename Arg2>
	std::string LogTraceString( const Arg1& arg1, const Arg2& arg2 ) { std::stringstream ss; ss << ',' << arg1 << ',' << arg2; return ss.str(); }


	// LogTraceクラス
	class LogTrace
	{
	public:
		LogTrace( const std::string& _file, int _line, const std::string& _func, const std::string& str )
			: file( _file )
			, line( _line )
			, func( _func )
		{
			BOOST_LOG_TRIVIAL( trace ) << " BEGIN : " << file << '(' << line << ')' << func << str;
		}

		~LogTrace( void )
		{
			BOOST_LOG_TRIVIAL( trace ) << " END   : " << file << '(' << line << ')' << func;
		}

	private:
		const std::string file;
		const int line;
		const std::string func;
	};
}

#define LOGTRACE(...) LogTrace logTrace( __FILE__, __LINE__, __FUNCTION__, LogTraceString( __VA_ARGS__ ) )
