#pragma once

namespace stltool 
{ 
	template <typename T>
	static void
	concat( const std::vector<std::vector<T> >& src, std::vector<T>& dst )
	{
		for( int i = 0, n = src.size(); i < n; ++i ) {
			dst.insert( dst.end(), src[i].begin(), src[i].end() );
		}
	}
};