#pragma once

#include <ostream>
#include <vector>

namespace stltool
{
	// 参考：http://d.hatena.ne.jp/kusano_prog/20110127/1296128291

	// コンテナを出力する汎用関数
	template <typename Container>
	std::ostream& printContainer( std::ostream& o, const Container& container )
	{
		Container::const_iterator it  = container.begin();
		Container::const_iterator end = container.end(); 

		o << "[";
		while( it != end ) {
			o << *it;
			++it;
			if ( it != end ) o << ", ";
		}
		o << "]";
		return o;
	}

	// vector出力用のWrapper関数
	// std::vector<T>を汎用的なContainerに置き換えると、
	// 既存のoperator<<と競合するケースがある。
	template <typename T>
	std::ostream& operator<<(std::ostream &o, const std::vector<T>& v)
	{
		return printContainer( o, v );
	}
}