#pragma once

#include <fstream>
#include <opencv2/core/core.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;

template<typename T>
class cvcsv2
{
public:
	template<typename Iterator>
	struct parseCSV
		: qi::grammar < Iterator, std::vector<T>() >
	{
		int rows;
		qi::rule<Iterator, std::vector<T>()> start;
		qi::rule<Iterator, std::vector<T>()> line;
		qi::rule<Iterator, void()> delim;
		qi::rule<Iterator, T()> elt;

		parseCSV() 
			: parseCSV::base_type(start)
			, rows(0)
		{
			start = line % qi::eol >> *qi::eol;
			line %= ( elt % delim >> *delim )[++boost::phoenix::ref(rows)];
			delim = qi::lit(',') | qi::lit(' ') | qi::lit(';');
			elt = qi::real_parser<T>();
		}
	};

	template<typename Iterator>
	struct generateCSV
		: karma::grammar < Iterator, std::vector<T>() >
	{
		int cols;
		karma::rule<Iterator, std::vector<T>()> start;
		karma::rule<Iterator, std::vector<T>()> line;
		karma::rule<Iterator, void()> delim;
		karma::rule<Iterator, T()> elt;

		generateCSV( int _cols) 
			: generateCSV::base_type(start)
			, cols( _cols )
		{
			start = karma::repeat(cols)[elt << delim] % karma::eol << karma::eol;
//			start = line % karma::eol << karma::eol;
//			line %= ( elt % delim << delim );
			delim = karma::lit(',');
			elt   = karma::real_generator<T>();
		}
	};


	static cv::Mat
	read(const std::string& file)
	{
		std::fstream ifs(file);
		std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		auto it = str.begin();

		parseCSV<std::string::iterator> parser;
		std::vector<T> result;
		bool success = qi::parse(it, str.end(), parser, result);

		return cv::Mat(result,true).reshape(1, parser.rows);
	}

	static int
	write( const std::string& file, const cv::Mat_<T>& src )
	{
		std::string str;

		std::back_insert_iterator<std::string> it( str );
		// ライティング処理
		generateCSV<std::back_insert_iterator<std::string> > wp( src.cols );

		std::vector<T> target;
		src.reshape( 1, 1 ).copyTo( target );

		bool success = karma::generate( it, wp, target );
		if ( !success ) {
			std::cerr << __FUNCTION__ << " GenerateFailed : " << file ;
			return -1;
		}

		std::ofstream ofs( file );
		if ( !ofs.is_open() ) {
			std::cerr << __FUNCTION__ << " OpenFailed : " << file ;
			return -1;
		}
		ofs << str;

		return 0;
	}
};

