//
// Created by Ullhor Greyiron on 6/18/21.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "utils.hpp"
#include "reversIterator.hpp"
#include "constReverseIterator.hpp"

namespace ft {
	template<class T>
	class VectorIterator : public std::iterator<std::random_access_iterator_tag, T> {
	public:
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;

		VectorIterator() : _p(0) {}

		VectorIterator(pointer p) : _p(p) {}

		VectorIterator(const VectorIterator &other) { _p = other._p; }

		~VectorIterator() {};

		VectorIterator &operator=(const VectorIterator &rh) {
			if (this != &rh)
				this->_p = rh._p;
			return (*this);
		}

		reference operator*() const { return *_p; }

		pointer operator->() const { return _p; }

		VectorIterator &operator--()    //prefix--
		{
			--_p;
			return (*this);
		}

		VectorIterator operator--(int)    //postfix--
		{
			VectorIterator tmp(*this);
			--(*this);
			return (tmp);
		}

		VectorIterator &operator++()    //prefix++
		{
			++_p;
			return (*this);
		}

		VectorIterator operator++(int)    //postfix--
		{
			VectorIterator tmp(*this);
			++(*this);
			return (tmp);
		}

		VectorIterator &operator+(int num) {
			_p += num;
			return *this;
		}

		VectorIterator &operator-(int num) {
			_p -= num;
			return *this;
		}

		friend bool operator==(const VectorIterator &lh, const VectorIterator &rh) {
			return (lh._p == rh._p);
		}

		friend bool operator!=(const VectorIterator &lh, const VectorIterator &rh) {
			return !(lh == rh);
		}

		pointer get_p() const {
			return (_p);
		}

	private:
		pointer _p;
	};

	template<class T>
	class ConstVectorIterator : public std::iterator<std::random_access_iterator_tag, T> {
	public:
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;

		ConstVectorIterator() {}

		ConstVectorIterator(pointer p) : _p(p) {}

		ConstVectorIterator(const VectorIterator<T> &other) { _p = other.get_p(); }

		ConstVectorIterator(const ConstVectorIterator &other) { _p = other._p; }

		~ConstVectorIterator() {};

		ConstVectorIterator &operator=(const ConstVectorIterator &rh) {
			if (this != &rh)
				this->_p = rh._p;
			return (*this);
		}

		reference operator*() const { return *_p; }

		pointer operator->() const { return _p; }

		ConstVectorIterator &operator--()    //prefix--
		{
			--_p;
			return (*this);
		}

		ConstVectorIterator operator--(int)    //postfix--
		{
			ConstVectorIterator tmp(*this);
			--(*this);
			return (tmp);
		}

		ConstVectorIterator &operator++()    //prefix++
		{
			++_p;
			return (*this);
		}

		ConstVectorIterator operator++(int)    //postfix--
		{
			ConstVectorIterator tmp(*this);
			++(*this);
			return (tmp);
		}

		ConstVectorIterator &operator+(int num) {
			_p += num;
			return *this;
		}

		ConstVectorIterator &operator-(int num) {
			_p -= num;
			return *this;
		}

		friend bool operator==(const ConstVectorIterator &lh, const ConstVectorIterator &rh) {
			return (lh._p == rh._p);
		}

		friend bool operator!=(const ConstVectorIterator &lh, const ConstVectorIterator &rh) {
			return !(lh == rh);
		}


		pointer get_p() const {
			return (_p);
		}

	private:
		pointer _p;
	};


	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef VectorIterator<T> iterator;
		typedef ConstVectorIterator<T> const_iterator;
		typedef ReverseIterator<iterator, pointer> reverse_iterator;
		typedef ConstReverseIterator<iterator, pointer> const_reverse_iterator;

		/******Constructors******/
		vector() : _data(0), _capacity(0), _size(0), _allocator(allocator_type()) {};

		explicit vector(const Allocator &alloc) : _data(0), _capacity(0), _size(0), _allocator(alloc) {};

		explicit vector(size_type count, const T &value = T(), const allocator_type &alloc = allocator_type()) {
			initVector(count, alloc);
			fill(0, count - 1, value);
		}

		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(),
			   typename std::enable_if<std::__is_input_iterator<InputIt>::value>::type * = 0) {
			initVector(first, last, alloc);
		}

		vector(const vector &other) {
			initVector(other.begin(), other.end(), other._allocator);
		}

		/******Destructor******/
		virtual ~vector() {
			clear();
			_allocator.deallocate(_data, _capacity);
		}

		/******Member functions******/
		vector &operator=(const vector &other) {
			vector tmp(other);
			swap(tmp);
			return *this;
		}

		void assign(size_type count, const T &value) {
			clear();
			_allocator.deallocate(_data, capacity());
			initVector(count, _allocator);
			fill(0, _size, value);
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last,
					typename std::enable_if<std::__is_input_iterator<InputIt>::value>::type * = 0) {
			clear();
			_allocator.deallocate(_data, capacity());
			initVector(first, last, _allocator);
		}

		/******Element access******/
		reference at(size_type pos) {
			if (pos < 0 || pos >= _size)
				throw std::out_of_range("bang");
			else
				return (*this)[pos];
		}

		reference operator[](size_type pos) {
			return *(_data + pos);
		}

		reference front() { return *_data; }

		const_reference front() const { return *_data; }

		reference back() { return *(_data + _size - 1); }

		const_reference back() const { return *(_data + _size - 1); }

		/******Iterators******/
		iterator begin() { return iterator(_data); }

		const_iterator begin() const { return const_iterator(_data); }

		reverse_iterator rbegin() { return reverse_iterator(_data + _size - 1); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(_data + _size - 1); }

		iterator end() { return iterator(_data + _size); }

		const_iterator end() const { return const_iterator(_data + _size); }

		reverse_iterator rend() { return reverse_iterator(_data - 1); }

		const_reverse_iterator rend() const { return const_reverse_iterator(_data); }

		/******Capacity******/
		bool empty() const { return _size == 0; }

		size_type size() const { return _size; }

		size_type max_size() const {
			return std::numeric_limits<size_type>::max() / sizeof(value_type);
		}

		void reserve(size_type new_cap) {
			if (new_cap <= _capacity)
				return;
			size_type sz = _size;
			pointer newData = createArray(new_cap);
			copyArray(&_data, &newData, _size);
			clear();
			_allocator.deallocate(_data, _capacity);
			_capacity = new_cap;
			_size = sz;
			_data = newData;
		}

		size_type capacity() const { return _capacity; }

		/******Member functions******/
		void clear() {
			while(_size > 0)
				pop_back();
		}

		iterator insert(iterator pos, const T &value) {
			size_type index = pos.get_p() - _data;
			insert(pos, 1, value);
			return (iterator(&_data[index]));
		}

		void insert(iterator pos, size_type count, const T &value) {
			size_type index = pos.get_p() - _data;
			moveRight(index, count);
			_size += count;
			for (; count > 0 ; count--, index++)
				_data[index] = value;
		}

		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last,
					typename std::enable_if<std::__is_input_iterator<InputIt>::value>::type * = 0) {
			size_type index = pos.get_p() - _data;
			size_type count = 0;
			for (InputIt tmpIt = InputIt(first); tmpIt != last; tmpIt++)
				++count;
			moveRight(index, count);
			for (; first != last; ++first, ++index) {
				_data[index] = *first;
			}
			_size += count;
		}

		iterator erase(iterator pos) {
			iterator nextIt = iterator(pos);
			nextIt++;
			return (erase(pos, nextIt));
		}

		iterator erase(iterator first, iterator last) {
			size_type count = 0;
			size_type index = first.get_p() - _data;
			for (; first != last; first++) {
				_allocator.destroy(&_data[first.get_p() - _data]);
				count++;
			}
			moveLeft(index+count, count);
			_size -= count;
			if (index >= _size)
				return end();
			else
				return iterator(&_data[index]);
		}

		void push_back(const T &value) {
			if (_size + 1 >= _capacity)
				reserve(_capacity * 2 + 1);
			_data[_size] = value;
			++_size;
		}

		void pop_back() {
			--_size;
			_allocator.destroy(&_data[_size]);
		}

		void resize(size_type count, T value = T()) {
			while (_size > count)
				pop_back();
			while (_size < count)
				push_back(value);
		}

		void swap(vector &other) {
			pointer tmp_data = other._data;
			size_type tmp_capacity = other._capacity;
			size_type tmp_size = other._size;
			allocator_type tmp_allocator = other._allocator;

			other._data = _data;
			other._capacity = _capacity;
			other._size = _size;
			other._allocator = _allocator;

			_data = tmp_data;
			_capacity = tmp_capacity;
			_size = tmp_size;
			_allocator = tmp_allocator;
		}

	private:
		pointer _data;
		size_type _capacity;
		size_type _size;
		allocator_type _allocator;

		void initVector(size_type count, const allocator_type alloc) {
			_size = count;
			_capacity = count;
			_allocator = alloc;
			_data = createArray(count);
		}

		template<class InputIt>
		void initVector(InputIt first, InputIt last, const allocator_type alloc,
						typename std::enable_if<std::__is_input_iterator<InputIt>::value>::type * = 0) {
			int count = 0;
			for (InputIt tmpIt = InputIt(first); tmpIt != last; tmpIt++)
				++count;
			initVector(count, alloc);
			for (size_type i = 0; first != last; i++, first++)
				_data[i] = *first;
		}

		pointer createArray(size_type count) {
			pointer array = _allocator.allocate(count);
			for (size_type i = 0; i < count; i++)
				_allocator.construct(&array[i], value_type());
			return array;
		}

		void copyArray(pointer *src, pointer *dst, size_type len) {
			pointer arr1 = *src;
			pointer arr2 = *dst;
			for (size_type i = 0; i < len; i++)
				arr2[i] = value_type(arr1[i]);
		}

		void fill(size_type start, size_type finish, value_type value) {
			for (size_type i = 0; i <= finish; i++)
				_data[i] = value;
		}

		void moveRight(size_type index, size_type count) {
			if (_size + count >= _capacity)
				reserve(_capacity * 2 + 1);
			for (size_type i = _size - 1; i >= index; i--)
				_data[i + count] = _data[i];
		}

		void moveLeft(size_type index, size_type count) {
			for (; index < _size; index++)
				_data[index - count] = _data[index];
		}

		friend bool operator==(const ft::vector<T, allocator_type> &lhs,
							   const ft::vector<T, allocator_type> &rhs) {
			typedef typename ft::vector<T, allocator_type>::size_type size_type;

			if (lhs._size != rhs._size || lhs._capacity != rhs.capacity() || lhs._allocator != rhs._allocator)
				return false;

			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}


		friend bool operator!=( const ft::vector<T,allocator_type>& lhs,
						 const ft::vector<T,allocator_type>& rhs )
		{
			return !(lhs == rhs);
		}


		friend bool operator<( const ft::vector<T,allocator_type>& lhs,
						const ft::vector<T,allocator_type>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}


		friend bool operator>( const ft::vector<T,allocator_type>& lhs,
						const ft::vector<T,allocator_type>& rhs )
		{
			return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
		}


		friend bool operator<=( const ft::vector<T,allocator_type>& lhs,
						 const ft::vector<T,allocator_type>& rhs )
		{
			return !(lhs > rhs);
		}


		friend bool operator>=( const ft::vector<T,allocator_type>& lhs,
						 const ft::vector<T,allocator_type>& rhs )
		{
			return !(lhs < rhs);
		}
	};

/******Non-member functions******/

}



#endif //FT_CONTAINERS_VECTOR_HPP
