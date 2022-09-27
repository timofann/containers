#ifndef CONTAINERS_ITERATORS2_HPP
#define CONTAINERS_ITERATORS2_HPP

#include <iostream>

namespace ft {


	template<bool IsConst, typename non_const_T, typename const_T>
	struct conditional { typedef non_const_T type; };
	template<typename non_const_T, typename const_T>
	struct conditional<true, non_const_T, const_T> { typedef const_T type; };


	template<typename T>
	struct remove_const { typedef T type; };
	template<typename T>
	struct remove_const<const T> { typedef T type; };


	template<bool condition, typename T = void>
	struct enable_if {};
	template<typename T>
	struct enable_if<true, T> { typedef T type; };


	struct input_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	template <bool IsConst, typename T, typename Category>
	class Iterator {
	public:
		typedef T value_type;
		typedef T& reference;
		typedef long difference_type;
		typedef T* pointer;
		typedef Category iterator_category;
	protected:
		T* _ptr;
	public:
		explicit Iterator() : _ptr(nullptr) {};
		explicit Iterator(T* ptr) : _ptr(ptr) {};
		Iterator<IsConst, T, Category>(const Iterator<IsConst, T, Category>& copy) : _ptr(copy.base()) {};
		Iterator&
		operator=(const Iterator<IsConst, T, Category> &other) {
			_ptr = other._ptr;
			return *this;
		};
//		Iterator&
//		operator=(const Iterator<false, T, Category> &other) {
//			_ptr = other._ptr;
//			return *this;
//		};
		Iterator&
		operator++() {
			++_ptr;
			return *this;
		};
		typename ft::conditional<IsConst, remove_const<T>&, const T&>::type
		operator*() const { return *_ptr; };
		T* base() const { return _ptr; };
		virtual ~Iterator() {};
	}; //class Iterator


	template <bool IsConst, typename T>
	class InputIterator : public Iterator<IsConst, T, input_iterator_tag> {
	public:
		explicit InputIterator() : Iterator<IsConst, T, input_iterator_tag>() {}; //explicit
		explicit InputIterator(T* ptr) : Iterator<IsConst, T, input_iterator_tag>(ptr) {}; //explicit
//		template<bool _IsConst>
		InputIterator(const InputIterator<false, T>& copy) : Iterator<false, T, input_iterator_tag>(copy) {};
//		InputIterator<false, T>(const InputIterator<false, T>& copy) : Iterator<false, T, input_iterator_tag>(copy) {};
//		InputIterator<true, T>(const InputIterator<false, T>& copy) : Iterator<true, T, input_iterator_tag>(copy) {};
		InputIterator& operator=(const InputIterator<IsConst, T> &other) {
			Iterator<IsConst, T, input_iterator_tag>::operator=(other);
			return *this;
		};
//		InputIterator& operator=(const InputIterator<false, T> &other) {
//			Iterator<IsConst, T, input_iterator_tag>::operator=(other);
//			return *this;
//		};
		InputIterator operator++(int) { // возможно const
			InputIterator tmp = *this; // херня неведомая (нужна конкретика по типам в шаблоне)
			++this->_ptr;
			return tmp;
		}
//		bool operator==(const InputIterator& other) const {
//			return this->_ptr == other._ptr;
//		};
//		bool operator!=(const InputIterator& other) const {
//			return this->_ptr != other._ptr;
//		};

		virtual ~InputIterator() {};

	}; //class InputIterator




} //namespace ft

#endif //CONTAINERS_ITERATORS2_HPP
