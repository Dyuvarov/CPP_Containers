#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <memory>
#include "utils.hpp"
#include "reversIterator.hpp"
#include "constReverseIterator.hpp"

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

		node_type* get_p() const
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

		node_type* get_p() const
		{
			return (_p);
		}
	private:
		node_type*	_p;
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
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;
	typedef ListIterator<T, _node> iterator;
	typedef ConstListIterator<T, _node> const_iterator;
	typedef ReverseIterator<iterator, _node*> reverse_iterator;
	typedef ConstReverseIterator<iterator, _node*> const_reverse_iterator;

	//*****************Constructors*****************//
	/**
	 * Default constructor. Constructs an empty container allocator_type allocator.
	 * The node created here is fictitious, it is not a real node of the list.
	 */
	explicit list(const allocator_type &alloc = allocator_type()) : _alloc(alloc) {
		initList(_alloc);
	}

	/**
	 * Constructs the container with the contents of the range [first, last)
	 * @first - iterator from
	 * @last  - iterator to
	 */
	template<class InputIt>
	list(InputIt first, InputIt last, const allocator_type &alloc = allocator_type(),
		 typename std::enable_if<std::__is_input_iterator<InputIt>::value>::type * = 0) : _alloc(alloc) {
		initList(_alloc);
		while (first != last) {
			push_back(*first);
			++first;
		}
	}

	/* Constructs the container with count copies of elements with value value. */
	explicit list(size_type count,
				  const T &value = T(),
				  const Alloc &alloc = Alloc())
			: _alloc(alloc) {
		initList(_alloc);
		for (size_type i = 0; i < count; i++)
			push_back(value);
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

	size_type size() {
		iterator it = begin();
		int count = 0;
		while (it != end()) {
			++count;
			++it;
		}
		return count;
	}

	size_type max_size() const { return nodeAllocator().max_size(); }

	//*****************Modifiers*****************//
	void clear() {
		_node *runner = _end->next;
		_node *tmp;
		while (runner != _end) {
			tmp = runner->next;
			runner->next = 0;
			runner->prev = 0;
			_nodeAlloc.destroy(runner);
			_nodeAlloc.deallocate(runner, 1);
			--_sz;
			runner = tmp;
		}
		_end->next = _end;
		_end->prev = _end;
	}

	iterator insert(iterator pos, const T &value) {
		_node *inserted = newNode(value);
		--pos;
		addAfter(pos.get_p(), inserted);
		return iterator(inserted);
	}

	void insert(iterator pos, size_type count, const T &value) {
		for (size_type i = 0; i < count; i++)
			insert(pos, value);
	}

	template<class InputIt>
	void insert(iterator pos, InputIt first, InputIt last,
				typename std::enable_if<std::__is_input_iterator<InputIt>::value>::type* = 0) {
		while (last != first) {
			insert(pos, *first);
			++first;
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
		addAfter(_end, newNode(value));
		++_sz;
	}

	void pop_front() {
		_node *front = _end->next;
		deleteFromChain(front);
		delete front;

	}

	void resize(size_type count, T value = T()) {
		size_type sz = size();
		while (sz > count)
		{
			pop_back();
			--sz;
		}
		while (sz < count)
		{
			push_back(value);
			++sz;
		}
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
	void merge(list &other) {
		if (this == &other)
			return;
		iterator thisRunner = begin();
		iterator otherRunner = other.begin();
		while (thisRunner != end() && otherRunner != other.end()) {
			if (*otherRunner < *thisRunner) {
				iterator tmp(otherRunner);
				++tmp;
				splice(thisRunner, other, otherRunner);
				otherRunner = tmp;
			} else
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
		iterator otherRunner = other.begin();
		while (thisRunner != end() && otherRunner != other.end()) {
			if (comp(*otherRunner, *thisRunner)) {
				iterator tmp(otherRunner);
				++tmp;
				splice(thisRunner, other, otherRunner);
				otherRunner = tmp;
			} else
				thisRunner++;
		}
		if (otherRunner != other.end())
			splice(thisRunner, other);
	}

	void splice(const_iterator pos, list &other) {
		splice(pos, other, other.begin(), other.end());
	}

	void splice(const_iterator pos, list &other, const_iterator it) {
		const_iterator nextIt(it);
		++nextIt;
		splice(pos, other, it, nextIt);
	}

	void splice(const_iterator pos, list &other,
				const_iterator first, const_iterator last) {
		while(first != last) {
			_node* node = first.get_p();
			++first;
			other.deleteFromChain(node);
			addAfter(pos.get_p()->prev, node);
		}
	}

	void remove(const T &value) {
		iterator it = begin();
		while (it != end()) {
			if (*it == value)
				it = erase(it);
			else
				++it;
		}
	}

	template<class UnaryPredicate>
	void remove_if(UnaryPredicate p) {
		iterator it = begin();
		while (it != end()) {
			if (p(*it))
				it = erase(it);
			else
				++it;
		}
	}

	void reverse() {
		_node* first = _end->next;
		_node* insertNeighbor = _end;
		while (_end->prev != first)
		{
			_node* node = _end->prev;
			deleteFromChain(node);
			addAfter(insertNeighbor, node);
			insertNeighbor = node;
		}
	}

	void unique() {
		iterator it = begin();
		while (it != end()) {
			iterator nit(it);
			++nit;
			while (*it == *nit)
				nit = erase(nit);
			it = nit;
		}
	}

	template<class BinaryPredicate>
	void unique(BinaryPredicate p) {
		iterator it = begin();
		while (it != end()) {
			iterator nit(it);
			++nit;
			if (p(*it, *nit)) {
				while (p(*it, *nit))
					nit = erase(nit);
			}
			++it;
		}
	}

	void sort() {
		_node *node = _end->next;
		while (node != _end && node->next != _end) {
			if (node->value > node->next->value) {
				_node *left = node;
				_node *right = node->next;

				right->next->prev = left;
				left->prev->next = right;
				right->prev = left->prev;
				left->next = right->next;
				left->prev = right;
				right->next = left;
				node = _end->next;
			} else
				node = node->next;
		}
	}

	template<class Compare>
	void sort(Compare comp) {
		_node *node = _end->next;
		while (node != _end && node->next != _end) {
			if (comp(node->next->value, node->value)) {
				_node *left = node;
				_node *right = node->next;

				right->next->prev = left;
				left->prev->next = right;
				right->prev = left->prev;
				left->next = right->next;
				left->prev = right;
				right->next = left;
				node = _end->next;
			} else
				node = node->next;
		}
	}

	list &operator=(const list &rh) //No exception operator=; copy & swap idiom here.
	{
		if (this != &rh) {
			list tmp(rh);
			swap(tmp);
		}
		return *this;
	}


private:
	typedef typename allocator_type::template rebind<_node>::other nodeAllocator;

	allocator_type _alloc;
	nodeAllocator _nodeAlloc;
	size_type _sz;
	_node *_end;

	void initList(const Alloc &alloc) {
		_alloc = alloc;
		_sz = 0;
		_end = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(_end, s_node());
		_end->next = _end;
		_end->prev = _end;
	}

	_node *newNode(const T &value) {
		_node *node = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(node, s_node());
		node->value = value;
		return node;
	}

	_node *addAfter(_node *neighbor, _node *newNode) {
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
	}

	void nodeSwap(_node** l, _node** r)
	{
		_node *tmp = *l;
		*l = *r;
		*r = tmp;
	}

};

	template< class T, class Alloc >
	bool operator==( const ft::list<T,Alloc>& lhs,
					 const ft::list<T,Alloc>& rhs )
	{

		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator!=( const ft::list<T,Alloc>& lhs,
					 const ft::list<T,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class T, class Alloc >
	bool operator<( const ft::list<T,Alloc>& lhs,
					const ft::list<T,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class T, class Alloc >
	bool operator<=( const ft::list<T,Alloc>& lhs,
					 const ft::list<T,Alloc>& rhs )
	{
		return (lhs == rhs || lhs < rhs);
	}

	template< class T, class Alloc >
	bool operator>( const ft::list<T,Alloc>& lhs,
					const ft::list<T,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>=( const ft::list<T,Alloc>& lhs,
					 const ft::list<T,Alloc>& rhs )
	{
		return (lhs == rhs || lhs > rhs);
	}
}



#endif //FT_CONTAINERS_LIST_HPP
