#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <memory>
//TODO:
//Constructor   -test it
//assign        -test it
//max_size      -test it
//clear
//insert
//erase
//pop_back
//pop_front
//resize
//swap
//merge
//splice
//remove
//remove_if
//reverse
//unique
//sort
//operator==
//operator!=
//operator<
//operator<=
//operator>
//operator>=

namespace ft
{
	template <class T, class nodeType>
	class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		typedef nodeType	node_type;
		typedef T			value_type;
		typedef value_type&	reference;
		typedef value_type*	pointer;

		ListIterator() :_p(0)	{}

		ListIterator(const ListIterator & other) : _p(other._p) {}

		ListIterator(node_type *p) : _p(p) {}

		virtual ~ListIterator()	{}

		ListIterator & operator=(const ListIterator & rh)
		{
			if (this != &rh)
				this->_p = rh._p;
			return (*this);
		}

		reference operator*() const	{ return _p->value; }

		pointer operator->() const	{ return &(_p->value);}

		ListIterator& operator--()
		{
			_p = _p->prev;
			return (*this);
		}

		ListIterator operator--(int)
		{
			ListIterator tmp(*this);
			--(*this);
			return (tmp);
		}

		ListIterator & operator++()		//prefix++
		{
			_p = _p->next;
			return (*this);
		}

		ListIterator operator++(int)	//postfix ++
		{
			ListIterator tmp(*this);
			++(*this);
			return (tmp);
		}

		friend bool operator==(const ListIterator & lh, const ListIterator & rh)
		{
			return (lh._p == rh._p);
		}

		friend bool operator!=(const ListIterator & lh, const ListIterator & rh)
		{
			return (lh._p != rh._p);
		}

		const node_type* get_p() const
		{
			return (_p);
		}

	private:
		node_type* _p;
	};

	template <class T, class nodeType>
	class ConstListIterator	: public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		typedef nodeType 			node_type;
		typedef T					value_type;
		typedef const value_type&	reference;
		typedef const value_type*	pointer;

		ConstListIterator(void) : _p(0)	{}

		ConstListIterator(const ListIterator<T, node_type> & other)	{ _p = other.get_p(); }

		ConstListIterator(const ConstListIterator & other) : _p(other._p) {}

		ConstListIterator(node_type *p) : _p(p) {}

		virtual ~ConstListIterator()	{}

		const ConstListIterator & operator=(const ConstListIterator & rh)
		{
			if (this != &rh)
				this->_p = rh._p;
			return (*this);
		}

		const ConstListIterator & operator=(const ListIterator<T, node_type> & rh)
		{
			this->_p = rh.get_p();
			return (*this);
		}

		reference operator*() const	{ return _p->value; }

		pointer operator->() const	{ return &(_p->value);}

		ConstListIterator & operator--()
		{
			_p = _p->prev;
			return (*this);
		}

		ConstListIterator operator--(int)
		{
			ConstListIterator tmp(*this);
			--(*this);
			return (tmp);
		}

		ConstListIterator & operator++()
		{
			_p = _p->next;
			return (*this);
		}

		ConstListIterator operator++(int)	//postfix ++
		{
			ConstListIterator tmp(*this);
			++(*this);
			return (tmp);
		}

		friend bool operator==(const ConstListIterator & lh, const ConstListIterator & rh)
		{
			return (lh._p == rh._p);
		}

		friend bool operator!=(const ConstListIterator & lh, const ConstListIterator & rh)
		{
			return (lh._p != rh._p);
		}

	private:
		const node_type*	_p;
	};

	template <class Iter>
	class ReverseIterator
	{
	public:
		typedef	typename Iter::value_type	value_type;
		typedef value_type&					reference;
		typedef value_type*					pointer;

		ReverseIterator()	{}

		ReverseIterator(const ReverseIterator& other)	: _base(other._base)	{}

		ReverseIterator(typename Iter::node_type *p)
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

	template <class Iter>
	class ConstReverseIterator
	{
	public:
		typedef	typename Iter::value_type	value_type;
		typedef const value_type&					reference;
		typedef const value_type*					pointer;

		ConstReverseIterator()	{}

		ConstReverseIterator(const ConstReverseIterator& other)	: _base(other._base)	{}

		ConstReverseIterator(const ReverseIterator<Iter>& other) : _base(other.get_base())	{}

		ConstReverseIterator(typename Iter::node_type *p)
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

		const ConstReverseIterator& operator=(const ReverseIterator<Iter>& rh)
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

	template < class T, class Alloc = std::allocator<T> >
class list
{
private:
	typedef struct s_node
	{
		T				value;
		struct s_node	*prev;
		struct s_node	*next;
	}				_node;

public:
	typedef T										value_type;
	typedef	Alloc									allocator_type;
	typedef std::size_t 							size_type;
	typedef std::ptrdiff_t 							difference_type;
	typedef typename Alloc::reference				reference;
	typedef typename Alloc::const_reference			const_reference;
	typedef typename Alloc::pointer					pointer;
	typedef typename Alloc::const_pointer			const_pointer;
	typedef ListIterator<T, _node>					iterator;
	typedef ConstListIterator<T, _node>				const_iterator;
	typedef ReverseIterator<iterator> 				reverse_iterator;
	typedef	ConstReverseIterator<iterator>			const_reverse_iterator;

	//*****************Constructors*****************//
	/**
	 * Default constructor. Constructs an empty container allocator_type allocator.
	 * The node created here is fictitious, it is not a real node of the list.
	 */
	explicit list(const allocator_type& alloc = allocator_type()) : _alloc(alloc)
	{
		initList(alloc);
	}

	/* Constructs the container with count copies of elements with value value. */
	explicit list(size_type count, const T& value = T(), const Alloc& alloc = Alloc())
	{
        initList(alloc);
        for (int i = 0; i < count; i++)
            push_back(value);
	}

	/**
	 * Constructs the container with the contents of the range [first, last)
	 * @first - iterator from
	 * @last  - iterator to
	 */
	template< class InputIt >
    list( InputIt first, InputIt last, const Alloc& alloc = Alloc() )
    {
	    initList(alloc);
	    while (first != last)
        {
            push_back(*first);
            ++first;
        }
    }

    list(const list& other)
    {
        initList( other._alloc);
        _nodeAlloc = other._nodeAlloc;
        if (other._sz == 0)
            return ;
        const_iterator ob = other.begin();
        const_iterator oe	= other.end();
        while (ob != oe)
        {
            push_back(*ob);
            ob++;
        }
    }

    void assign( size_type count, const T& value )
    {
        list tmp(count, value);
        *this = tmp;
    }

    template< class InputIt >
    void assign( InputIt first, InputIt last )
    {
        list tmp(first, last);
        *this = tmp;
    }

	~list()
    {
		clear();
        _nodeAlloc.destroy(_end);
        _nodeAlloc.deallocate(_end, 1);
	}

	//*****************Element access*****************//
	reference 		front()	{ return _end->next->value; }

	const_reference front() const { return _end->next->value; }

	reference 		back() { return _end->prev->value; }

	const_reference back() const { return _end->prev->value; }

	//*****************Iterators*****************//
	iterator 		begin()			{ return iterator(_end->next); }

	const_iterator	begin() const	{ return const_iterator(_end->next); }

	reverse_iterator rbegin()		{ return reverse_iterator (_end->prev); };

	iterator 		end()			{ return iterator(_end); }

	const_iterator	end() const		{ return const_iterator(_end); }

	reverse_iterator rend()		{ return reverse_iterator (_end); };

	//*****************Capacity*****************//

	bool empty() const
	{
		return ((_sz == 0) ? true : false);
	}

	size_type size() const  { return _sz; }

    size_type max_size() const  {return nodeAllocator().max_size(); }

	//*****************Modifiers*****************//
    void clear()
    {
        _node* runner = _end->next;
        _node* tmp;
        _end->next = 0;
        while(runner->next)
        {
            tmp = runner->next;
            runner->next = 0;
            runner->prev = 0;
            _nodeAlloc.destroy(runner);
            _nodeAlloc.deallocate(runner, 1);
            --_sz;
            runner = tmp;
        }
    }

	void push_back(const T& value)
	{
		_node* tmp = newNode(value);
		tmp->prev = _end->prev;
		tmp->next = _end;
		_end->prev->next = tmp;
		_end->prev = tmp;
		++_sz;
	}

	list& operator=(const list& rh) //No exception operator=; copy & swap idiom here.
	{
		if (this != &rh)
		{
			list tmp(rh);
			swap(tmp);
		}
		return *this;
	}


private:
	typedef typename allocator_type::template rebind<_node>::other nodeAllocator;

	allocator_type	_alloc;
	nodeAllocator	_nodeAlloc;
	size_type		_sz;
	_node*			_end;

	void initList(const Alloc& alloc)
    {
	    _alloc = alloc;
        _sz = 0;
        _end = _nodeAlloc.allocate(1);
        _nodeAlloc.construct(_end, s_node());
        _end->next = _end;
        _end->prev = _end;
    }

	_node*	newNode(const T& value)
	{
		_node* node = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(node, s_node());
		node->value = value;
		return node;
	}

	_node*	addAfter(_node* neighbor, _node* newNode)
	{
		newNode->next = neighbor->next;
		newNode->next->prev = newNode;
		neighbor->next = newNode;
		newNode->prev = neighbor;

		return (newNode);
	}

	void swap(list& src)
	{
	    _node* tmp = src._end;
        src._end = this->_end;
        this->_end = tmp;
	}
};
}

#endif //FT_CONTAINERS_LIST_HPP
