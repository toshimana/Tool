#pragma once

#include <numeric>

namespace stltool
{
	// STL—paccumulate‚ÌWrapper
	template <typename Container, class T>
	T accumulate( const Container& container, T init )
	{
		return std::accumulate( container.begin(), container.end(), init );
	}

	template <typename Container, class T, typename Func >
	T accumulate( const Container& container, T init, Func func )
	{
		return std::accumulate( container.begin(), container.end(), init, func );
	}
};