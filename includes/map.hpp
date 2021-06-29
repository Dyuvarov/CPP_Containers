//
// Created by Ullhor Greyiron on 6/29/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "utils.hpp"
namespace ft {

template <class T, class nodeType>
class MapIterator : public std::iterator<std::bidirectional_iterator_tag, T> {

private:
	nodeType*	_p;

public:
	typedef nodeType	node_type;
	typedef T			value_type;
	typedef value_type&	reference;
	typedef value_type*	pointer;

	MapIterator() :_p(0)	{}

	MapIterator(const MapIterator & other) : _p(other._p) {}

	MapIterator(node_type *p) : _p(p) {}

	virtual ~MapIterator()	{}

	MapIterator & operator=(const MapIterator & rh)
	{
		if (this != &rh)
			this->_p = rh._p;
		return (*this);
	}

	reference operator*() const	{ return _p->data; }

	pointer operator->() const	{ return &(_p->data);}


	MapIterator& operator--()
	{
		//TODO:this
	}

	MapIterator operator--(int)
	{
		MapIterator tmp(*this);
		--(*this);
		return (tmp);
	}

	MapIterator & operator++()		//prefix++
	{
		//TODO:this
	}

	MapIterator operator++(int)	//postfix ++
	{
		MapIterator tmp(*this);
		++(*this);
		return (tmp);
	}

	friend bool operator==(const MapIterator & lh, const MapIterator & rh)
	{
		return (lh._p == rh._p);
	}

	friend bool operator!=(const MapIterator & lh, const MapIterator & rh)
	{
		return (lh._p != rh._p);
	}

	node_type* get_p() const
	{
		return (_p);
	}
};

template <class T, class nodeType>
class MapConstIterator : public std::iterator<std::bidirectional_iterator_tag, T> {

	typedef nodeType	node_type;
	typedef T			value_type;
	typedef value_type&	reference;
	typedef value_type*	pointer;


};

template <class Key, class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {

private:
	typedef struct s_node {
		ft::pair<const Key, T>*		data;
		struct s_node				*parent;
		struct s_node				*left;
		struct s_node				*right;
	} _node;

public:
	typedef Key 										key_type;
	typedef	T											mapped_type;
	typedef ft::pair<const key_type,mapped_type>		value_type;
	typedef std::size_t									size_type;
	typedef std::ptrdiff_t 								difference_type;
	typedef Compare										key_compare;
	typedef	Allocator									allocator_type;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef typename Allocator::pointer					pointer;
	typedef typename Allocator::const_pointer			const_pointer;
	typedef MapIterator<value_type, _node>				iterator;
	typedef MapConstIterator<value_type, _node>			const_iterator;
	typedef ReverseIterator<iterator, pointer>			reverse_iterator;
	typedef ConstReverseIterator<iterator, pointer>		const_reverse_iterator;

	class value_compare : public std::binary_function<value_type,value_type,bool>
	{
	private:
		Compare comp;
		value_compare (Compare c) : comp(c) {}
	public:
		bool operator() (const value_type& x, const value_type& y) const {return comp(x.first, y.first);}
	};

	explicit map( const Compare& comp = key_compare(), const Allocator& alloc = Allocator() )
	{
		initMap(comp, alloc);
	}

	template< class InputIt >
	map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator(),
		 typename ft::enable_if<std::__is_input_iterator<InputIt>::value>::type* = 0)
	{
		initMap(comp, alloc);
		//TODO: add inserts
	}

	map( const map& other )
	{
		//TODO: this
	}

	map( const map& other, const Allocator& alloc )
	{
		//TODO: this
	}

	ft::pair<iterator, bool> insert(const value_type &value )
	{
		if (_root == 0)
		{
			_root = new_node((value_type &) value);
			_root->parent = 0;
			return (ft::make_pair(iterator(_root), true));
		}
		else
		{
			_node* place = findPlace(value, _root);
			if (!(value._first < place->data->_first) && !(value._first > place->data->_first))
				return ft::make_pair(iterator(place), false);

			_node* newNode = new_node(value);
			newNode->parent = place;
			if (value._first < place->data->_first)
				place->left = newNode;
			else if (value._first > place->data->_first)
				place->right = newNode;
			return ft::make_pair(iterator(newNode), true);
		}
	}

	iterator insert( iterator hint, const value_type& value )
	{
		//TODO: this
	}

	template< class InputIt >
	void insert( InputIt first, InputIt last )
	{
		//TODO: this
	}

private:

typedef typename allocator_type::template rebind<_node>::other nodeAllocator;

allocator_type	_alloc;
nodeAllocator	_nodeAlloc;
_node*			_root;
Compare			_comp;
size_type		_sz;

_node* new_node(const value_type& pair)
{
	_node* newNode = _nodeAlloc.allocate(1);
	_nodeAlloc.construct(newNode);
	newNode->data = _alloc.allocate(1);
	_alloc.construct(newNode->data, pair);
	newNode->left = 0;
	newNode->right = 0;
	return (newNode);
}

void initMap(const Compare comp, const Allocator& alloc)
{
	_comp = comp;
	_alloc = alloc;
	_sz = 0;
	_root = 0;
}

_node*	findPlace(const value_type& value, _node* root)
{
	if(value._first < root->data->_first)
	{
		if (root->left == 0)
			return root;
		else
			return findPlace(value, root->left);
	}
	else if (value._first > root->data->_first)
	{
		if (root->right == 0)
			return root;
		else
			return findPlace(value, root->right);
	}
	else
		return root;
}

};

}


#endif //FT_CONTAINERS_MAP_HPP
