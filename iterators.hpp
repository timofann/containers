#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <iostream>
#include <type_traits>

namespace ft {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	template<bool B, typename T1, typename T2>
	struct conditional { typedef T2 type; };
	template<typename T1, typename T2>
	struct conditional<false, T1, T2> { typedef T1 type; };


	template <bool IsConst, typename T, typename Category>
	class Iterator {
	public:
		typedef T value_type;
		typedef T& reference;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef Category iterator_category;

	protected:
		pointer _ptr;
		typedef const T& const_reference;

//		template<bool B, typename T1, typename T2>
//		struct conditional { typedef T2 type; };
//		template<typename T1, typename T2>
//		struct conditional<false, T1, T2> { typedef T1 type; };

	public:
		explicit Iterator() : _ptr(0) {};
		explicit Iterator(value_type* ptr) : _ptr(ptr) {};
		Iterator(const Iterator<true, T, Category>& copy) { _ptr = copy._ptr; };
		Iterator(const Iterator<false, T, Category>& copy) { _ptr = copy._ptr; };
		Iterator &operator=(const Iterator<true, T, Category>& copy) {
			_ptr = copy._ptr;
			return *this;
		};
		Iterator&
		operator=(const Iterator<false, T, Category>& copy) {
			_ptr = copy._ptr;
			return *this;
		};
		typename ft::conditional<IsConst, Iterator, const Iterator>::type&
		operator++() {
			++_ptr;
			return *this;
		};
		typename ft::conditional<IsConst, reference, const_reference>::type
		operator*() const { return *_ptr; };
		~Iterator() {};

	}; // class Iterator


	template <bool IsConst, typename T>
	class InputIterator : public Iterator< IsConst, T, input_iterator_tag> {
	public:
		typedef typename Iterator< IsConst, T, input_iterator_tag>::value_type value_type;
		typedef typename Iterator< IsConst, T, input_iterator_tag>::reference reference;
		typedef typename Iterator< IsConst, T, input_iterator_tag>::pointer pointer;
		typedef typename Iterator< IsConst, T, input_iterator_tag>::difference_type difference_type;
		typedef typename Iterator< IsConst, T, input_iterator_tag>::iterator_category iterator_category;

	protected:
		typedef typename Iterator< IsConst, T, input_iterator_tag>::const_reference const_reference;

	public:
		explicit InputIterator() : Iterator<IsConst, T, input_iterator_tag>() {};
		explicit InputIterator(value_type* ptr) : Iterator<IsConst, T, input_iterator_tag>(ptr) {};

		InputIterator &operator=(const InputIterator& copy) {
			Iterator<IsConst, T, input_iterator_tag>::operator=(copy);
			return *this;
		};

		typename ft::conditional<IsConst, reference, const_reference>::type
		operator*() const;

		typename ft::conditional<IsConst, InputIterator, const InputIterator>::type&
		operator++() {
			++Iterator<IsConst, T, input_iterator_tag>::_ptr;
			return *this;
		};

		const InputIterator operator++(int) {
			InputIterator tmp = *this;
			++Iterator<IsConst, T, input_iterator_tag>::_ptr;
			return tmp;
		};

		bool operator==(const InputIterator& other) const {
			return Iterator<IsConst, T, input_iterator_tag>::_ptr == other.Iterator<IsConst, T, input_iterator_tag>::_ptr;
		};

		bool operator!=(const InputIterator& other) const {
			return Iterator<IsConst, T, input_iterator_tag>::_ptr != other.Iterator<IsConst, T, input_iterator_tag>::_ptr;
		};

//		using Iterator<IsConst, T, input_iterator_tag>::operator++;

	}; // class InputIterator


} // namespace ft

#endif
