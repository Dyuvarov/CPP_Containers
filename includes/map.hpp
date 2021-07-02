//
// Created by Ullhor Greyiron on 6/29/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "utils.hpp"
#include "reversIterator.hpp"
#include "constReverseIterator.hpp"
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

	reference operator*() const	{ return *(_p->data); }

	pointer operator->() const	{ return (_p->data);}


	MapIterator& operator--()
	{
		if (_p->left)
		{
			_p = _p->left;
			while (_p->right)
				_p = _p->right;
		}
		else
		{
			nodeType* prev;
			do
			{
				prev = _p;
				_p = _p->parent;
			}
			while (_p->parent && _p->left == prev);
		}
		return *this;
	}

	MapIterator operator--(int)
	{
		MapIterator tmp(*this);
		--(*this);
		return (tmp);
	}

	MapIterator & operator++()		//prefix++
	{
		if (_p->right)
		{
			_p = _p->right;
			while (_p->left)
				_p = _p->left;
		}
		else
		{
			nodeType* prev;
			do
			{
				prev = _p;
				_p = _p->parent;
			}
			while (_p->parent && _p->right == prev);
		}
		return *this;
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
private:
	const nodeType*	_p;

public:
	typedef nodeType	node_type;
	typedef T			value_type;
	typedef value_type&	reference;
	typedef value_type*	pointer;

	MapConstIterator() :_p(0)	{}

	MapConstIterator(const MapConstIterator & other) : _p(other._p) {}

	MapConstIterator(const MapIterator<T, node_type> & other)	{ _p = other.get_p(); }

	MapConstIterator(node_type *p) : _p(p) {}

	virtual ~MapConstIterator()	{}

	MapConstIterator & operator=(const MapConstIterator & rh)
	{
		if (this != &rh)
			this->_p = rh._p;
		return (*this);
	}

	MapConstIterator & operator=(const MapIterator<T, node_type> & rh)
	{
		this->_p = rh.get_p();
			return (*this);
	}

	reference operator*() const	{ return *(_p->data); }

	pointer operator->() const	{ return _p->data;}

	MapConstIterator& operator--()
	{
		if (_p->left)
		{
			_p = _p->left;
			while (_p->right)
				_p = _p->right;
		}
		else
		{
			const nodeType* prev;
			do
			{
				prev = _p;
				_p = _p->parent;
			}
			while (_p->parent && _p->left == prev);
		}
		return *this;
	}

	MapConstIterator operator--(int)
	{
		MapConstIterator tmp(*this);
		--(*this);
		return (tmp);
	}

	MapConstIterator & operator++()		//prefix++
	{
		if (_p->right)
		{
			_p = _p->right;
			while (_p->left)
				_p = _p->left;
		}
		else
		{
			const nodeType* prev;
			do
			{
				prev = _p;
				_p = _p->parent;
			}
			while (_p->parent && _p->right == prev);
		}
		return *this;
	}

	MapConstIterator operator++(int)	//postfix ++
	{
		MapConstIterator tmp(*this);
		++(*this);
		return (tmp);
	}

	friend bool operator==(const MapConstIterator & lh, const MapConstIterator & rh)
	{
		return (lh._p == rh._p);
	}

	friend bool operator!=(const MapConstIterator & lh, const MapConstIterator & rh)
	{
		return (lh._p != rh._p);
	}

	node_type* get_p() const
	{
		return (_p);
	}
};

template <class Key, class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {

private:
	typedef struct s_node {
		ft::pair<const Key, T>		*data;
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
	typedef ReverseIterator<iterator, _node*>			reverse_iterator;
	typedef ConstReverseIterator<iterator, _node*>		const_reverse_iterator;

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
		 typename std::enable_if<std::__is_input_iterator<InputIt>::value>::type* = 0)
	{
		initMap(comp, alloc);
		insert(first, last);
	}

	map( const map& other )
	{
		initMap(other._comp, other._alloc);
		insert(other.begin(), other.end());
	}

	~map()
	{
		clear();
		_alloc.deallocate(_nil->data, 1);
		_nodeAlloc.destroy(_nil);
		_nodeAlloc.deallocate(_nil, 1);
	}

	map& operator=( const map& other )
	{
		if (*this != other)
		{
			map<Key, T, Compare, Allocator> tmp = map(other);
			swap(tmp);
		}
		return *this;
	}

	T& operator[]( const Key& key )
	{
		return insert(ft::make_pair(key, mapped_type()))._first->_second;
	}


	/*****ITERATORS*****/

	/**
	 * returns most left node
	 * @return mapIterator
	 */
	iterator begin()
	{
		_node* node = _root;
		while (node->left)
			node = node->left;
		return (iterator(node));
	}

	const_iterator begin() const
	{
		_node* node = _root;
		while (node->left)
			node = node->left;
		return (const_iterator(node));
	}

	/**
	 * returns nil
	 */
	iterator end() { return iterator(_nil); }

	const_iterator end() const { return const_iterator(_nil); }

	reverse_iterator rbegin()
	{
		_node* node = _root;
		while (node->right)
			node = node->right;
		return (reverse_iterator(node));
	}

	const_reverse_iterator rbegin() const
	{
		_node* node = _root;
		while (node->right)
			node = node->right;
		return (const_reverse_iterator(node));
	}

	reverse_iterator rend() {return reverse_iterator(_nil); }

	const_reverse_iterator rend() const {return const_reverse_iterator(_nil); }

	/*****CAPACITY*****/
	bool empty() const { return _nil == _root; }

	size_type size() const
	{
		size_type size = 0;
		for(const_iterator it = begin(); it != end(); it++)
			++size;
		return size;
	}

	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

	/*****MODIFIERS*****/
	void clear() { erase(begin(), end()); }

	ft::pair<iterator, bool> insert(const value_type &value)
	{
		if (_root == _nil)
		{
			_node* node = new_node(value, _root->parent);
			node->parent = _nil;
			_root = node;
			_nil->right = node;
			_nil->left = node;
			return ft::make_pair(iterator(node), true);
		}

		_node* place = findPlace(value._first, _root);
		_node* node = new_node(value, place);
		if (_comp(value._first, place->data->_first))
		{
			place->left = node;
			return ft::make_pair(iterator(node), true);
		}
		else if (_comp(place->data->_first, value._first))
		{
			place->right = node;
			return ft::make_pair(iterator(node), true);
		}
		return ft::make_pair(iterator(place), false);
	}

	iterator insert( iterator hint, const value_type& value )
	{
		_node* local_root = hint.get_p();
		if (local_root == _nil)
		{
			_node* node = new_node(value, _root->parent);
			node->right = _nil;
			_nil->parent = node;
			_root = node;
			return iterator(node);
		}

		_node* place = findPlace(value._first, local_root);
		if (_comp(value._first, place->data->_first))
		{
			_node* node = new_node(value, place);
			place->left = node;
			return iterator(node);
		}
		else if (_comp(place->data->_first, value._first))
		{
			_node* node = new_node(value, place);

			if (place->right == _nil)
			{
				node->right = _nil;
				_nil->parent = node;
			}

			place->right = node;
			return iterator(node);
		}
		return iterator(place);
	}

	template< class InputIt >
	void insert( InputIt first, InputIt last,
				 typename ft::enable_if<std::__is_input_iterator<InputIt>::value>::type* = 0)
	{
		while (first != last)
		{
			insert(*first);
			++first;
		}
	}


	void erase(iterator pos)
	{
		_node* node = pos.get_p();
		_node* parent = node->parent;
		if (!parent)
			return;

		_node** place;
		_node** place_other;
		if (_comp(node->data->_first, parent->data->_first))
		{
			place = &parent->left;
			place_other = &parent->right;
		}
		else
		{
			place = &parent->right;
			place_other = &parent->left;
		}

		if (node->right && !node->left)
		{
			*place = node->right;
			node->right->parent = parent;
		}
		else if (!node->right && node->left)
		{
			*place = node->left;
			node->left->parent = parent;
		}
		else if (node->right && node->left)
		{
			*place = node->right;
			node->right->parent = parent;
			insertNode(node->left);
		}
		else
			*place = 0;

		if (parent == _nil)
			*place_other = *place;

		_alloc.destroy(node->data);
		_alloc.deallocate(node->data, 1);
		_nodeAlloc.destroy(node);
		_nodeAlloc.deallocate(node, 1);
	}

	void erase( iterator first, iterator last )
	{
		while (first != last)
		{
			iterator tmp(first);
			first++;
			erase(tmp);
		}
	}

	size_type erase( const key_type& key )
	{
		_node* node = findEqual(key, _root);
		if (node)
		{
			iterator pos = iterator(node);
			if (pos != end())
			{
				erase(pos);
				return 1;
			}
		}
		return 0;
	}

	void swap( map& other )
	{
		allocator_type tmp_alloc = _alloc;
		this->_alloc = other._alloc;
		other._alloc = tmp_alloc;

		nodeAllocator tmp_nodeAlloc = _nodeAlloc;
		this->_nodeAlloc = other._nodeAlloc;
		other._nodeAlloc = tmp_nodeAlloc;

		_node*	tmp_root = _root;
		this->_root = other._root;
		other._root = tmp_root;

		_node*	tmp_nil = _nil;
		this->_nil = other._nil;
		other._nil = tmp_nil;

		Compare tmp_compare = _comp;
		this->_comp = other._comp;
		other._comp = tmp_compare;
	}

	/*****LOOKUP*****/
	size_type count( const Key& key ) const
	{
		if(findEqual(key, _root))
			return 1;
		else
			return 0;
	}

	iterator find( const Key& key )
	{
		_node* place = findEqual(key, _root);
		if (place)
			return iterator(place);
		else
			return iterator(_nil);
	}

	const_iterator find( const Key& key ) const
	{
		_node* place = findEqual(key, _root);
		if (place)
			return const_iterator(place);
		else
			return const_iterator(_nil);
	}

	iterator lower_bound(const Key& key )
	{
		iterator it1 = begin();
		while (it1 != end())
		{
			if (!_comp(it1->_first, key))
				break;
			++it1;
		}
		return it1;
	}

	const_iterator lower_bound( const Key& key ) const
	{
		const_iterator it1 = begin();
		while (it1 != end())
		{
			if (!_comp(key, it1->_first))
				break;
			++it1;
		}
		return it1;
	}

	ft::pair<iterator,iterator> equal_range( const Key& key )
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	iterator upper_bound( const Key& key )
	{
		iterator it1 = begin();
		while (it1 != end())
		{
			if (_comp(key, it1->_first))
				break;
			++it1;
		}
		return it1;
	}

	const_iterator upper_bound( const Key& key ) const
	{
		const_iterator it1 = begin();
		while (it1 != end())
		{
			if (_comp(key, it1->_first))
				break;
			++it1;
		}
		return it1;
	}

	key_compare key_comp() const
	{
		return _comp;
	}

	value_compare value_comp() const
	{
		return value_compare();
	}

	/*****NON-MEMBER******/
	friend bool operator==( const ft::map<Key,T,Compare,Allocator>& lhs,
					 const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		if (lhs.size() != rhs.size() || lhs._alloc != rhs._alloc)
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	friend bool operator!=( const ft::map<Key,T,Compare,Allocator>& lhs,
					 const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return !(lhs == rhs);
	}

	friend bool operator<( const ft::map<Key,T,Compare,Allocator>& lhs,
						   const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	friend bool operator>( const ft::map<Key,T,Compare,Allocator>& lhs,
						   const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return (!(lhs < rhs) && !(lhs == rhs));
	}

	friend bool operator<=( const ft::map<Key,T,Compare,Allocator>& lhs,
					 const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return (!(lhs > rhs));
	}

	friend bool operator>=( const ft::map<Key,T,Compare,Allocator>& lhs,
					const ft::map<Key,T,Compare,Allocator>& rhs )
	{
		return (!(lhs < rhs));
	}

private:

typedef typename allocator_type::template rebind<_node>::other nodeAllocator;

allocator_type	_alloc;
nodeAllocator	_nodeAlloc;
_node*			_root;
_node*			_nil;
Compare			_comp;


_node* new_node(const value_type& pair, _node* parent)
{
	_node* newNode = _nodeAlloc.allocate(1);
	_nodeAlloc.construct(newNode);
	newNode->data = _alloc.allocate(1);
	_alloc.construct(newNode->data, pair);
	newNode->left = 0;
	newNode->right = 0;
	newNode->parent = parent;
	return (newNode);
}

void initMap(const Compare comp, const Allocator& alloc)
{
	_comp = comp;
	_alloc = alloc;

	_root = _nodeAlloc.allocate(1);
	_nodeAlloc.construct(_root, _node());
	_root->data = _alloc.allocate(1);
	_root->left = 0;
	_root->right = 0;
	_root->parent = 0;
	_nil = _root;
}

_node*	findPlace(const Key key, _node* root) const
{

	if(_comp(key, root->data->_first))
	{
		if (root->left == 0)
			return root;
		else
			return findPlace(key, root->left);
	}
	else if (_comp(root->data->_first, key))
	{
		if (root->right == 0)
			return root;
		else
			return findPlace(key, root->right);
	}
	else
		return root;
}

_node*	findEqual(const Key key, _node* root) const
{
	_node* place = findPlace(key, _root);
	if (!_comp(place->data->_first, key) && !_comp(key, place->data->_first))
		return place;
	else
		return 0;
}

void 	insertNode(_node* node)
{
	_node* place = findPlace(node->data->_first, _root);
	if(_comp(node->data->_first, place->data->_first))
		place->left = node;
	else
		place->right = node;
	node->parent = place;
}

};

}


#endif //FT_CONTAINERS_MAP_HPP
