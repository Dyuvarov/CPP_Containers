
#ifndef FT_CONTAINERS_REVERSITERATOR_HPP
#define FT_CONTAINERS_REVERSITERATOR_HPP
template <class Iter, class ptr>
class ReverseIterator
{
public:
	typedef	typename Iter::value_type	value_type;
	typedef value_type&					reference;
	typedef value_type*					pointer;

	ReverseIterator()	{}

	ReverseIterator(const ReverseIterator& other)	: _base(other._base)	{}

	ReverseIterator(ptr p)
	{
		Iter tmp(p);
		_base = tmp;
	}

	virtual ~ReverseIterator()	{};

	ReverseIterator	& operator=(const ReverseIterator& rh)
	{
		if (this != &rh)
			this->_base = rh._base;
		return *this;
	}

	reference operator*()	{ return _base.operator*(); }

	pointer operator->() const	{ return _base.operator->(); }

	ReverseIterator& operator--()
	{
		++_base;
		return (*this);
	}

	ReverseIterator operator--(int)
	{
		ReverseIterator tmp(*this);
		_base++;
		return (tmp);
	}

	ReverseIterator& operator++()
	{
		--_base;
		return (*this);
	}

	ReverseIterator operator++(int)
	{
		ReverseIterator tmp(*this);
		_base--;
		return (tmp);
	}

	friend bool operator==(const ReverseIterator & lh, const ReverseIterator & rh)
	{
		return (lh._base.get_p() == rh._base.get_p());
	}

	friend bool operator!=(const ReverseIterator & lh, const ReverseIterator & rh)
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

#endif //FT_CONTAINERS_REVERSITERATOR_HPP
