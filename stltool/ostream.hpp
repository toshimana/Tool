#pragma once

#include <ostream>
#include <vector>

namespace stltool
{
	// �Q�l�Fhttp://d.hatena.ne.jp/kusano_prog/20110127/1296128291

	// �R���e�i���o�͂���ėp�֐�
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

	// vector�o�͗p��Wrapper�֐�
	// std::vector<T>��ėp�I��Container�ɒu��������ƁA
	// ������operator<<�Ƌ�������P�[�X������B
	template <typename T>
	std::ostream& operator<<(std::ostream &o, const std::vector<T>& v)
	{
		return printContainer( o, v );
	}
}