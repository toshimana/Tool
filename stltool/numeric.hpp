#pragma once

#include <numeric>

namespace stltool
{
	// STL�paccumulate��Wrapper
	template <typename Container, class T>
	T accumulate( Container container, T init )
	{
		return std::accumulate( container.begin(), container.end(), init );
	}
};