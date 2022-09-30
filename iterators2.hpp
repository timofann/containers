#ifndef CONTAINERS_ITERATORS2_HPP
#define CONTAINERS_ITERATORS2_HPP

#include <iostream>
#include "type_traits.hpp"

namespace ft {

	struct input_iterator_tag {};
	struct forward_iterator_tag         :   public input_iterator_tag {};
	struct bidirectional_iterator_tag   :   public forward_iterator_tag {};
	struct random_access_iterator_tag   :   public bidirectional_iterator_tag {};


	template <typename It>
	struct iterator_traits {
		typedef typename It::value_type                 value_type;
		typedef typename It::reference                  reference;
		typedef typename It::difference_type            difference_type;
		typedef typename It::pointer                    pointer;
		typedef typename It::iterator_category          iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef typename T                              value_type;
		typedef typename T&                             reference;
		typedef typename long                           difference_type;
		typedef typename T*                             pointer;
		typedef typename ft::random_access_iterator_tag iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		typedef typename T                              value_type;
		typedef typename const T&                       reference;
		typedef typename long                           difference_type;
		typedef typename const T*                       pointer;
		typedef typename ft::random_access_iterator_tag iterator_category;
	};


	namespace detail {

		template <typename It>
		void do_advance(It& it, typename iterator_traits<It>::difference_type n, input_iterator_tag) {
			while (n > 0) { --n; ++it; }
		}

		template <typename It>
		void do_advance(It& it, typename iterator_traits<It>::difference_type n, bidirectional_iterator_tag) {
			while (n > 0) { --n; ++it; }
			while (n < 0) { ++n; --it; }
		}

		template<class It>
		void do_advance(It& it, typename iterator_traits<It>::difference_type n, std::random_access_iterator_tag) {
			it += n;
		}

	} // namespace detail

	template <typename InputIt, typename Distance>
	void advance(InputIt& it, Distance n) {
		detail::do_advance(it, typename iterator_traits<InputIt>::difference_type(n), typename iterator_traits<InputIt>::iterator_category());
	}


	template <bool IsConst, typename T, typename Category>
	class Iterator {
	public:
		typedef T           value_type;
		typedef T&          reference;
		typedef long        difference_type;
		typedef T*          pointer;
		typedef Category    iterator_category;
	protected:
		T* _ptr;
	public:
		explicit Iterator() : _ptr(nullptr) {};
		explicit Iterator(T* ptr) : _ptr(ptr) {};
		Iterator(const Iterator<IsConst, T, Category>& copy) : _ptr(copy.base()) {};
		Iterator&
		operator=(const Iterator<IsConst, T, Category> &other) {
			_ptr = other._ptr;
			return *this;
		};
		Iterator&
		operator++() {
			++_ptr;
			return *this;
		};
		T&
		operator*() { return *_ptr; };
		T*
		operator->() {
			return _ptr; }
		T* base() const { return _ptr; };
		virtual ~Iterator() {};
	}; //class Iterator


	template <typename T, typename Category>
	class Iterator<true, T, Category> {
	public:
		typedef T           value_type;
		typedef const T&    reference;
		typedef long        difference_type;
		typedef const T*    pointer;
		typedef Category    iterator_category;
	protected:
		T* _ptr;
	public:
		explicit Iterator() : _ptr(nullptr) {};
		explicit Iterator(T* ptr) : _ptr(ptr) {};
		Iterator(const Iterator<true, T, Category>& copy) : _ptr(copy.base()) {};
		Iterator(const Iterator<false, T, Category>& copy) : _ptr(copy.base()) {};
		Iterator&
		operator=(const Iterator<true, T, Category> &other) {
			_ptr = other._ptr;
			return *this;
		};
		Iterator&
		operator=(const Iterator<false, T, Category> &other) {
			_ptr = other._ptr;
			return *this;
		};
		Iterator&
		operator++() {
			++_ptr;
			return *this;
		};
		const T&
		operator*() const { return *_ptr; };
		const T* base() const { return _ptr; };
		virtual ~Iterator() {};
	}; //class Iterator (ConstIterator)


	template <bool IsConst, typename T>
	class InputIterator : public Iterator<IsConst, T, input_iterator_tag> {
	public:
		explicit InputIterator() : Iterator<IsConst, T, input_iterator_tag>() {};
		explicit InputIterator(T* ptr) : Iterator<IsConst, T, input_iterator_tag>(ptr) {};
		InputIterator(const InputIterator<IsConst, T>& copy) : Iterator<IsConst, T, input_iterator_tag>(copy) {};
		InputIterator(const InputIterator<!IsConst, T>& copy) : Iterator<IsConst, T, input_iterator_tag>(copy) {};
		InputIterator& operator=(const InputIterator<IsConst, T> &other) {
			Iterator<IsConst, T, input_iterator_tag>::operator=(other);
			return *this;
		};
		InputIterator& operator=(const InputIterator<!IsConst, T> &other) {
			Iterator<IsConst, T, input_iterator_tag>::operator=(other);
			return *this;
		};
		InputIterator operator++(int) { // возможно const
			InputIterator tmp = *this; // херня неведомая (нужна конкретика по типам в шаблоне)
			++this->_ptr;
			return tmp;
		}
		bool operator==(const InputIterator<IsConst, T>& other) const {
			return this->base() == other.base(); };
		bool operator==(const InputIterator<!IsConst, T>& other) const {
			return this->base() == other.base(); };
		bool operator!=(const InputIterator<IsConst, T>& other) const {
			return this->base() != other.base(); };
		bool operator!=(const InputIterator<!IsConst, T>& other) const {
			return this->base() != other.base(); };
		T* operator->() {
			return &a;
		}
		virtual ~InputIterator() {};

	}; //class InputIterator




} //namespace ft

#endif //CONTAINERS_ITERATORS2_HPP
