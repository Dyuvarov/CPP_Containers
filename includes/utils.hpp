//
// Created by Ullhor Greyiron on 6/18/21.
//

#ifndef FT_CONTAINERS_UTILS_HPP
#define FT_CONTAINERS_UTILS_HPP

namespace ft
{

template <bool, class _Tp = void> struct enable_if {};
template <class _Tp> struct enable_if<true, _Tp> {typedef _Tp type;};

/*****PAIR*****/

template <class T1, class T2>
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	T1	_first;
	T2	_second;

	pair() : _first(), _second() {}

	pair( const T1& x, const T2& y ) : _first(x), _second(y) {}

	template< class U1, class U2 >
	pair( const pair<U1, U2>& p ) : _first(p._first), _second(p._second) {}

	pair( const pair& p ) : _first(p._first), _second(p._second) {}

	pair& operator=(pair const& p) {
		_first = p._first;
		_second = p._second;
		return *this;
	}

	template< class U1, class U2 >
	pair& operator=( const pair<U1,U2>& other )
	{
		_first = other.first;
		_second = other.second;
		return *this;
	}

	friend bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (lhs._first == rhs._first && lhs._second == rhs._second);
	}

	friend bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(lhs == rhs);
	}
};

template< class T1, class T2 >
const pair<T1,T2> make_pair( T1 t, T2 u )
{
	return pair<T1, T2>(t, u);
}

template< class T1, class T2 >
bool operator==( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template< class T1, class T2 >
bool operator!=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
{
	return (!lhs == rhs);
}

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 begin1, InputIterator1 end1, InputIterator2 begin2)
{
	for (; begin1 != end1; begin1++, begin2++)
	{
		if (*begin1 != *begin2)
			return false;
	}
	return true;
}

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
							  InputIt2 first2, InputIt2 last2 )
{
	while (first1 != last1 && first2 != last2)
	{
		if (*first1 < *first2)
			return true;
		else if (*first1 > *first2)
			return false;
		else
		{
			++first1;
			++first2;
		}
	}
	if (first1 == last1 && first2 != last2)
		return true;
	return false;
}

}

#endif //FT_CONTAINERS_UTILS_HPP
