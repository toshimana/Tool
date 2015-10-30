#pragma once

#include <algorithm>

namespace stltool 
{
	// STL�pcount_if��Wrapper
	template <typename Container, typename Predicate>
	size_t count_if( Container container, Predicate pred )
	{
		return std::count_if( container.begin(), container.end(), pred );
	}

	// STL�psort��Wrapper
	template <typename Container>
	void sort( const Container& input, Container& output )
	{
		output.resize( input.size() );
		std::copy( input.begin(), input.end(), output.begin() );

		std::sort( output.begin(), output.end() );
	}

	// STL�psort��Wrapper
	template <typename Container, typename Compare>
	void sort( const Container& input, Container& output, Compare comp )
	{
		output.resize( input.size() );
		std::copy( input.begin(), input.end(), output.begin() );

		std::sort( output.begin(), output.end(), comp );
	}


	// STL�pshuffle��Wrapper
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