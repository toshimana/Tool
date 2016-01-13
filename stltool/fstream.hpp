#pragma once

#include <fstream>

namespace stltool 
{ 
	template<typename Container>
	void saveToCSV( const Container& src, const std::string& path, std::ios_base::openmode openmode = std::ios::out )
	{
		std::ofstream ofs( path, openmode );
		if( !ofs.is_open() ) {
			std::string errMsg( __FUNCTION__ );
			throw std::invalid_argument( errMsg + path );
		}

		for( auto it = src.begin(), endIt = src.end(); it != endIt; ++it ) {
			ofs << *it << std::endl;
		}
	}

	template<typename T>
	void loadFromCSV( std::vector<T>& dst, const std::string& path )
	{
		std::ifstream ifs( path );
		if( !ifs.is_open() ) {
			std::string errMsg( __FUNCTION__ );
			throw std::invalid_argument( errMsg + path );
		}

		while( !ifs.eof() ) {
			T elt;
			ifs >> elt;
			dst.push_back( elt );
		}
	}
};