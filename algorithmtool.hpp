#pragma once

#include <algorithm>

namespace algorithmtool 
{
	// STL—pcount_if‚ÌWrapper
	template <typename Container, typename Predicate>
	size_t count_if( Container container, Predicate pred )
	{
		return std::count_if( container.begin(), container.end(), pred );
	}

	// 
	template <typename Container >
	void shuffle( const Container& input, Container& output )
	{
		// copy
		output.resize( input.size() );
		std::copy( input.begin(), input.end(), output.begin() );

		// shuffle
		std::random_shuffle( output.begin(), output.end() );
	}
};