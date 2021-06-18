//
// Created by Ullhor Greyiron on 6/18/21.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP
namespace ft
{
template <class T>
class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
	typedef	T	value_type;
	typedef	*T	pointer;
	typedef &T	reference;

	VectorIterator() : _p(0) {}
	VectorIterator(pointer p) : _p(p) {}
	VectorIterator(const VectorIterator& other) { _p = other._p; }
	~VectorIterator() {};

	VectorIterator& operator=(const VectorIterator& rh)
	{
		if (this != &rh)
			this->_p = rh._p;
		return (*this);
	}

	reference operator*() const	{ return *_p; }

	pointer operator->() const	{ return _p; }

	VectorIterator& operator--()	//prefix--
	{
		--_p;
		return (*this);
	}

	VectorIterator operator--(int)	//postfix--
	{
		VectorIterator tmp(*this);
		--(*this);
		return (tmp);
	}

	VectorIterator & operator++()	//prefix++
	{
		++_p;
		return (*this);
	}

	VectorIterator operator++(int)	//postfix--
	{
		VectorIterator tmp(*this);
		++(*this);
		return (tmp);
	}

	friend bool operator==(const VectorIterator & lh, const VectorIterator & rh)
	{
		return (lh._p == rh._p);
	}

	friend bool operator!=(const VectorIterator & lh, const VectorIterator & rh)
	{
		return !(lh == rh);
	}

	pointer* get_p() const
	{
		return (_p);
	}

private:
	pointer _p;
};


template<class T, class Allocator = std::allocator <T> >
class vector {
public:
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef Allocator::pointer pointer;
	typedef Allocator::const_pointer const_pointer;

};
}
#endif //FT_CONTAINERS_VECTOR_HPP
