#ifndef FT_CONTAINERS_CONSTREVERSEITERATOR_HPP
#define FT_CONTAINERS_CONSTREVERSEITERATOR_HPP

#include "reversIterator.hpp"

template <class Iter, class ptr>
class ConstReverseIterator
{
public:
	typedef	typename Iter::value_type			value_type;
	typedef const value_type&					reference;
	typedef const value_type*					pointer;

	ConstReverseIterator()	{}

	ConstReverseIterator(const ConstReverseIterator& other)	: _base(other._base)	{}

	ConstReverseIterator(const ReverseIterator<Iter, ptr>& other) : _base(other.get_base())	{}

	ConstReverseIterator(ptr p)
	{
		Iter tmp(p);
		_base = tmp;
	}

	virtual ~ConstReverseIterator()	{};

	const ConstReverseIterator& operator=(const ConstReverseIterator& rh)
	{
		if (this != &rh)
			this->_base = rh._base;
		return *this;
	}

	const ConstReverseIterator& operator=(const ReverseIterator<Iter, ptr>& rh)
	{
		this->_base = rh.get_base();
		return *this;
	}

	reference operator*()	{ return _base.operator*(); }

	pointer operator->() const	{ return _base.operator->(); }

	ConstReverseIterator& operator--()
	{
		++_base;
		return (*this);
	}

	ConstReverseIterator operator--(int)
	{
		ConstReverseIterator tmp(*this);
		_base++;
		return (tmp);
	}

	ConstReverseIterator& operator++()
	{
		--_base;
		return (*this);
	}

	ConstReverseIterator operator++(int)
	{
		ConstReverseIterator tmp(*this);
		_base--;
		return (tmp);
	}

	friend bool operator==(const ConstReverseIterator & lh, const ConstReverseIterator & rh)
	{
		return (lh._base.get_p() == rh._base.get_p());
	}

	friend bool operator!=(const ConstReverseIterator & lh, const ConstReverseIterator & rh)
	{
		return (!(lh == rh));
	}

	const Iter get_base() const
	{
		return (_base);
	}

private:
	Iter _base;
};

#endif //FT_CONTAINERS_CONSTREVERSEITERATOR_HPP
