#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP
#include "vector.hpp"

namespace ft
{

template< class T, class Container = vector<T> >
class stack
{
public:
	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

	explicit stack( const Container& cont = Container() ) : _baseContainer(cont) {}
	stack( const stack& other ) : _baseContainer(other._baseContainer) {}
	~stack() {}

	stack& operator=( const stack& other )
	{
		_baseContainer = other._baseContainer;
		return (*this);
	}

	reference top() { return _baseContainer.back(); }
	const_reference top() const {return _baseContainer.back(); }

	bool empty() const {return  _baseContainer.empty(); }
	size_type size() {return  _baseContainer.size(); }

	void push( const value_type& value ) { _baseContainer.push_back(value); }
	void pop() { _baseContainer.pop_back(); }

	container_type getCnt() const {return _baseContainer; }
private:
	container_type	_baseContainer;
};

	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getCnt() == rhs.getCnt();
	};
	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getCnt() != rhs.getCnt();
	};
	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getCnt() < rhs.getCnt();
	};
	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getCnt() <= rhs.getCnt();
	};
	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getCnt() > rhs.getCnt();
	};
	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getCnt() >= rhs.getCnt();
	};

}

#endif //FT_CONTAINERS_STACK_HPP
