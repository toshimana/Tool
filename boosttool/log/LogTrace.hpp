#pragma once

#include <stdio.h>

#include <string>
#include <boost/log/trivial.hpp>

namespace {

	// vectorの自動出力用
#include "../../stltool/ostream.hpp"
	using namespace stltool;
	
	// 可変長引数を文字列に変換するクラス
	std::string LogTraceString( std::stringstream& ss ){ return ss.str(); }
	
	template <typename Arg1>
	std::string LogTraceString( std::stringstream& ss, const Arg1& arg1 ){ ss << ',' << arg1; return ss.str(); }

	template <typename Arg1,typename Arg2>
	std::string LogTraceString( std::stringstream& ss,const Arg1& arg1, const Arg2& arg2 ) { ss << ',' << arg1; return LogTraceString( ss, arg2 ); }


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

#define LOGTRACE(...) LogTrace logTrace( __FILE__, __LINE__, __FUNCTION__, LogTraceString( std::stringstream(), __VA_ARGS__ ) )
