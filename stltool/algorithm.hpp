#pragma once

#include <algorithm>

namespace stltool 
{
	// STL用count_ifのWrapper
	template <typename Container, typename Predicate>
	size_t count_if( Container container, Predicate pred )
	{
		return std::count_if( container.begin(), container.end(), pred );
	}

	// STL用sortのWrapper
	template <typename Container>
	void sort( const Container& input, Container& output )
	{
		output.resize( input.size() );
		std::copy( input.begin(), input.end(), output.begin() );

		std::sort( output.begin(), output.end() );
	}

	// STL用sortのWrapper
	template <typename Container, typename Compare>
	void sort( const Container& input, Container& output, Compare comp )
	{
		output.resize( input.size() );
		std::copy( input.begin(), input.end(), output.begin() );

		std::sort( output.begin(), output.end(), comp );
	}

	// STL用transformのWrapper
	template <typename Container1, typename Container2, typename Func>
	void transform( const Container1& src, Container2& dst, Func func )
	{
		dst.resize( src.size() );
		std::transform( src.begin(), src.end(), dst.begin(), func );
	}

	// STL用for_eachのWrapper
	template <typename Container, typename Func>
	void for_each( Container& container, Func func )
	{
		std::for_each( container.begin(), container.end(), func );
	}

	// STL用shuffleのWrapper
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