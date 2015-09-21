#pragma once

namespace stltool 
{ 
	// 型変換用id関数
	template <typename T, typename U>
	U id( const T& value ) { return static_cast<U>( value ); }

	// STL用copyのWrapper
	template <typename Container1, typename Container2>
	void copy( Container1 src, Container2 dst )
	{
		dst.resize( src.size() );
		std::copy( src.begin(), src.end(), dst.begin() );
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
	void for_each( Container container, Func func )
	{
		std::for_each( container.begin(), container.end(), func );
	}

	template <typename SrcIterator1, typename SrcIterator2, typename DstIterator, typename Func>
	void zipWith( const SrcIterator1& srcBegin1, const SrcIterator1& srcEnd1, const SrcIterator2& srcBegin2, const SrcIterator2& srcEnd2, DstIterator& dstBegin, Func func )
	{
		SrcIterator1 srcIt1 = srcBegin1;
		SrcIterator2 srcIt2 = srcBegin2;
		DstIterator  dstIt  = dstBegin;
		for( ; ( ( srcIt1 != srcEnd1 ) && ( srcIt2 != srcEnd2 ) ); ++srcIt1, ++srcIt2, ++dstIt )
		{
			*dstIt = func( *srcIt1, *srcIt2 );
		}
	}

	template <typename SrcContainer1, typename SrcContainer2, typename DstContainer, typename Func>
	void zipWith( const SrcContainer1& srcContainer1, const SrcContainer2& srcContainer2, DstContainer& dstContainer, Func func )
	{
		dstContainer.resize( std::min( srcContainer1.size(), srcContainer2.size() ) );
		zipWith( srcContainer1.begin(), srcContainer1.end(), srcContainer2.begin(), srcContainer2.end(), dstContainer.begin(), func );
	}
	
	template <typename T>
	void concat( const std::vector<std::vector<T> >& src, std::vector<T>& dst )
	{
		for( int i = 0, n = src.size(); i < n; ++i ) {
			dst.insert( dst.end(), src[i].begin(), src[i].end() );
		}
	}

	template <typename Container>
	void splitAt( size_t firstSize, const Container& input, Container& first, Container& second )
	{
		size_t secondSize = input.size() - firstSize;

		first.resize( firstSize );
		std::copy( input.begin(), input.begin()+firstSize, first.begin() );

		second.resize( secondSize );
		std::copy( input.begin()+firstSize, input.end(), second.begin() );
	}
};