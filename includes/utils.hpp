//
// Created by Ullhor Greyiron on 6/18/21.
//

#ifndef FT_CONTAINERS_UTILS_HPP
#define FT_CONTAINERS_UTILS_HPP

namespace ft
{
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
