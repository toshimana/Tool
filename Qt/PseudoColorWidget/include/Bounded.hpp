#pragma once

#include <limits>

template <typename T>
struct Bounded
{
	const T minBound;
	const T maxBound;

	Bounded( const T& _min = std::numeric_limits<T>::min(), const T& _max = std::numeric_limits<T>::max() )
		: minBound( _min ), maxBound( _max )
	{
	}
};