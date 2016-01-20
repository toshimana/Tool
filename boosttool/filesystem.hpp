#pragma once

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>


namespace boost
{
	namespace filesystem
	{
		// http://stackoverflow.com/questions/10167382/boostfilesystem-get-relative-path
		template < >
		path& path::append<path::iterator>( path::iterator begin, path::iterator end, const codecvt_type& cvt)
		{
			for( ; begin != end ; ++begin )
				*this /= *begin;
			return *this;
		}
		template < >
		path& path::append<path::iterator>( path::iterator begin, path::iterator end )
		{
			for( ; begin != end ; ++begin )
				*this /= *begin;
			return *this;
		}
	}
}

namespace boosttool
{
	namespace fs = boost::filesystem;

    // Return path when appended to a_From will resolve to same as a_To
    boost::filesystem::path make_relative( boost::filesystem::path a_From, boost::filesystem::path a_To )
    {
        a_From = boost::filesystem::absolute( a_From ); a_To = boost::filesystem::absolute( a_To );
        boost::filesystem::path ret;
        boost::filesystem::path::const_iterator itrFrom( a_From.begin() ), itrTo( a_To.begin() );
        // Find common base
        for( boost::filesystem::path::const_iterator toEnd( a_To.end() ), fromEnd( a_From.end() ) ; itrFrom != fromEnd && itrTo != toEnd && *itrFrom == *itrTo; ++itrFrom, ++itrTo );
        // Navigate backwards in directory to reach previously found base
        for( boost::filesystem::path::const_iterator fromEnd( a_From.end() ); itrFrom != fromEnd; ++itrFrom )
        {
            if( (*itrFrom) != "." )
                ret /= "..";
        }
        // Now navigate down the directory branch
        ret.append( itrTo, a_To.end() );
        return ret;
    }


	void 
	make_filelist( const fs::path& dir, std::vector<fs::path>& filelist, std::function<bool(const fs::path&)> isValid )
	{
		filelist.clear();

		BOOST_FOREACH( const fs::path& p, std::make_pair( fs::directory_iterator(dir),
			                                              fs::directory_iterator() ) ) 
		{
			if ( !fs::is_directory( p ) ) {
				if ( isValid( p ) ) {
					filelist.push_back( p );
				}
			}
		}
	}
};