#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <memory>
//TODO:
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

		const node_type* get_p() const
		{
			return (_p);
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
class list {
private:
	typedef struct s_node {
		T value;
		struct s_node *prev;
		struct s_node *next;
	} _node;

public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;
	typedef ListIterator<T, _node> iterator;
	typedef ConstListIterator<T, _node> const_iterator;
	typedef ReverseIterator<iterator> reverse_iterator;
	typedef ConstReverseIterator<iterator> const_reverse_iterator;

	//*****************Constructors*****************//
	/**
	 * Default constructor. Constructs an empty container allocator_type allocator.
	 * The node created here is fictitious, it is not a real node of the list.
	 */
	explicit list(const allocator_type &alloc = allocator_type()) : _alloc(alloc) {
		initList(alloc);
	}

	/* Constructs the container with count copies of elements with value value. */
	explicit list(size_type count, const T &value = T(), const Alloc &alloc = Alloc()) {
		initList(alloc);
		for (int i = 0; i < count; i++)
			push_back(value);
	}

	/**
	 * Constructs the container with the contents of the range [first, last)
	 * @first - iterator from
	 * @last  - iterator to
	 */
	template<class InputIt>
	list(InputIt first, InputIt last, const Alloc &alloc = Alloc()) {
		initList(alloc);
		while (first != last) {
			push_back(*first);
			++first;
		}
	}

	list(const list &other) {
		initList(other._alloc);
		_nodeAlloc = other._nodeAlloc;
		if (other._sz == 0)
			return;
		const_iterator ob = other.begin();
		const_iterator oe = other.end();
		while (ob != oe) {
			push_back(*ob);
			ob++;
		}
	}

	void assign(size_type count, const T &value) {
		list tmp(count, value);
		*this = tmp;
	}

	template<class InputIt>
	void assign(InputIt first, InputIt last) {
		list tmp(first, last);
		*this = tmp;
	}

	~list() {
		clear();
		_nodeAlloc.destroy(_end);
		_nodeAlloc.deallocate(_end, 1);
	}

	//*****************Element access*****************//
	reference front() { return _end->next->value; }

	const_reference front() const { return _end->next->value; }

	reference back() { return _end->prev->value; }

	const_reference back() const { return _end->prev->value; }

	//*****************Iterators*****************//
	iterator begin() { return iterator(_end->next); }

	const_iterator begin() const { return const_iterator(_end->next); }

	reverse_iterator rbegin() { return reverse_iterator(_end->prev); };

	iterator end() { return iterator(_end); }

	const_iterator end() const { return const_iterator(_end); }

	reverse_iterator rend() { return reverse_iterator(_end); };

	//*****************Capacity*****************//

	bool empty() const {
		return ((_sz == 0) ? true : false);
	}

	size_type size() const
	{
		iterator it = begin();
		int count = 0;
		while (it != end())
			++count;
		return count;
	}

	size_type max_size() const { return nodeAllocator().max_size(); }

	//*****************Modifiers*****************//
	void clear() {
		_node *runner = _end->next;
		_node *tmp;
		_end->next = 0;
		while (runner->next) {
			tmp = runner->next;
			runner->next = 0;
			runner->prev = 0;
			_nodeAlloc.destroy(runner);
			_nodeAlloc.deallocate(runner, 1);
			--_sz;
			runner = tmp;
		}
	}

	iterator insert(iterator pos, const T &value) {
		_node *inserted = newNode(value);
		inserted->next = pos.get_p();
		inserted->prev = pos.get_p()->prev;
		pos.get_p()->prev->next = inserted;
		pos.get_p()->prev = inserted;
		++_sz;
		return iterator(inserted);
	}

	void insert(iterator pos, size_type count, const T &value) {
		for (size_type i = 0; i < count; i++)
			insert(pos, value);
	}

	template<class InputIt>
	void insert(iterator pos, InputIt first, InputIt last) {
		while (last != first) {
			insert(pos, *first);
			**first;
		}
	}

	iterator erase(iterator pos) {
		if (pos.get_p() == end())
			return end();
		_node *erasing = pos.get_p();
		erasing->prev->next = erasing->next;
		erasing->next->prev = erasing->prev;
		pos++;
		delete erasing;
		--_sz;
		return pos;
	}

	iterator erase(iterator first, iterator last) {
		iterator l;
		while (first != last) {
			l = erase(first);
			++first;
		}
		return l;
	}

	void push_back(const T &value) {
		_node *tmp = newNode(value);
		tmp->prev = _end->prev;
		tmp->next = _end;
		_end->prev->next = tmp;
		_end->prev = tmp;
		++_sz;
	}

	void pop_back() {
		_node *back = _end->prev;
		deleteFromChain(back);
		delete back;
	}

	void push_front(const T &value) {
		addAfter(_end->next, newNode(value));
		++_sz;
	}

	void pop_front() {
		_node *front = _end->next;
		deleteFromChain(front);
		delete back;

	}

	void resize(size_type count, T value = T()) {
		while (_sz > count)
			pop_back();
		while (_sz < count)
			push_back(value);
	}

	void swap(list &src) {
		nodeSwap(&_end, &src._end);

		size_type curSize = _sz;
		_sz = src._sz;
		src._sz = curSize;

		nodeAllocator curNodeAlloc = _nodeAlloc;
		_nodeAlloc = src._nodeAlloc;
		src._nodeAlloc = curNodeAlloc;

		allocator_type curAlloc = _alloc;
		_alloc = src._alloc;
		src._alloc = curAlloc;
	}

	//*****************Operations*****************//
	void merge(list &other)
	{
		if (this == &other)
			return;
		iterator thisRunner = begin();
		iterator otherRunner= other.begin;
		while (thisRunner != end() && otherRunner != other.end())
		{
			if (*otherRunner < *thisRunner)
			{
				iterator tmp(otherRunner);
				++tmp;
				splice(thisRunner, other, otherRunner);
				otherRunner = tmp;
			}
			else
				thisRunner++;
		}
		if (otherRunner != other.end())
			splice(thisRunner, other);
	}

	template<class Compare>
	void merge(list &other, Compare comp) {
		if (this == &other)
			return;
		iterator thisRunner = begin();
		iterator otherRunner= other.begin;
		while (thisRunner != end() && otherRunner != other.end())
		{
			if (comp(*otherRunner, *thisRunner))
			{
				iterator tmp(otherRunner);
				++tmp;
				splice(thisRunner, other, otherRunner);
				otherRunner = tmp;
			}
			else
				thisRunner++;
		}
		if (otherRunner != other.end())
			splice(thisRunner, other);
	}

	void splice(const_iterator pos, list &other)
	{
		splice(pos, other, other.begin(), other.end());
	}

	void splice( const_iterator pos, list& other, const_iterator it )
	{
		const_iterator nextIt(it);
		++nextIt;
		splice(pos, other, it, nextIt);
	}

	void splice(const_iterator pos, list &other,
				const_iterator first, const_iterator last)
	{
		for (; first!= last; first++)
		{
			addAfter(pos.get_p()->prev, first.get_p());
			other._sz--;
		}
	}

	void remove( const T& value )
	{
		iterator it = begin();
		while (it != end())
		{
			if (*it == value)
				it = erase(it);
			else
				++it;
		}
	}

	template< class UnaryPredicate >
	void remove_if( UnaryPredicate p )
	{
		iterator it = begin();
		while (it != end())
		{
			if (p(*it))
				it = erase(it);
			else
				++it;
		}
	}

	void reverse()
	{
		_node* head = _end->next;
		_node* ass = _end->prev;
		_node* cur = head;
		_node* prev = _end;
		_node* next = cur->next;
		while (cur != _end)
		{
			next = cur->next;
			cur->next = prev;
			cur->prev = next;
			cur = next;
			prev = cur;
		}
		_end->prev = head;
		_end->next = ass;
	}

	void unique()
	{
		iterator it = begin();
		while (it != end())
		{
			iterator nit(it);
			++nit;
			while (*it == *nit)
				nit = erase(nit);
			it = nit;
		}
	}

	template< class BinaryPredicate >
	void unique( BinaryPredicate p )
	{
		iterator it = begin();
		while (it != end())
		{
			iterator nit(it);
			++nit;
			if (p(*it, *nit))
			{
				while (p(*it, *nit))
					nit = erase(nit);
			}
			++it;
		}
	}

	void sort()
	{
		//TODO: DOIT
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

	void deleteFromChain(_node* node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		--_sz;
	}

	void nodeSwap(_node** l, _node** r)
	{
		_node *tmp = l;
		*l = *r;
		*r = tmp;
	}

};
}

#endif //FT_CONTAINERS_LIST_HPP
