#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <cstdlib>
#include <vector>

namespace ft {

	template< class T, class Allocator = std::allocator<T> >
	class Vector {

	public:

		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
//		typedef std::ptrdiff_t difference_type;
		typedef typename Allocator::difference_type difference_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef typename std::vector<T, Allocator>::iterator iterator;
		typedef typename std::vector<T, Allocator>::const_iterator const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	private:

		value_type *arr_;
		size_type size_;
		size_type capacity_;
		const Allocator &alloc_;

		void
		cleanVector() {
			for (size_type i = 0; i < size_; ++i)
				alloc_.destroy(&(arr_[i])); // не понятно, нужен все-таки адрес или объект
			alloc_.deallocate(arr_, capacity_);
		};

		value_type*
		initVector(size_type cap) {
			if (cap <= 0)
				throw std::out_of_range("Capacity less then zero"); // какая-то херня
			value_type *dst;
			cap > 0 ? dst = alloc_.allocate(cap)
			        : dst = nullptr;
			return dst;
		};

		void
		fillVector(value_type* arr, size_type count, const_reference value) {
			size_type i = 0;
			try {
				for (; i < count; ++i)
					alloc_.construct(&(arr[i]), value);
			} catch (...) {
				for (size_type j = 0; j < i; ++j)
					alloc_.destroy(&(arr[j]));
				throw;
			}
		};

		value_type*
		copyVector(value_type *src, size_type src_size, size_type dst_capacity) {
			value_type *dst = initVector(dst_capacity);
			if (dst == nullptr || src == nullptr)
				return dst;
			try {
				std::uninitialized_copy(src, src + std::min(src_size, dst_capacity), dst); //вероятное увеличение времени работы из-за избегания перегружения оператора & (-> addresof)
			} catch (...) {
				alloc_.deallocate(dst, dst_capacity);
				throw;
			}
			return dst;
		};

	public:

		Vector() : arr_(nullptr), size_(0),
		           capacity_(0),  alloc_(Allocator()) {};

		explicit
		Vector(const Allocator &alloc) : arr_(nullptr), size_(0),
		                                 capacity_(0),  alloc_(alloc) {};

		explicit
		Vector(size_type count, const_reference value = value_type(),
		       const Allocator &alloc = Allocator()) : size_(count),
		                                               capacity_(count),
		                                               alloc_(alloc) {
			capacity_ > 0 ? arr_ = alloc_.allocate(capacity_) : arr_ = nullptr;
			for (size_type i = 0; i < size_; ++i)
				alloc_.construct(&(arr_[i]), value);
			// [i] на сколько сдвигает указатель? // не понятно, нужен все-таки адрес или объект
		};

		template<class InputIt>
		Vector(InputIt first, InputIt last,
		       const Allocator &alloc = Allocator()) : alloc_(alloc) {
			InputIt first2(first);
			size_ = 0;
			for (; first != last; ++first)
				++size_;
			capacity_ = size_;
			capacity_ > 0 ? arr_ = alloc_.allocate(capacity_) : arr_ = nullptr;
			for (size_type i = 0; i < size_; ++i)
				alloc_.construct(&(arr_[i]), *(first2 + i));
			// [i] на сколько сдвигает указатель? // не понятно, нужен все-таки адрес или объект
		};

		Vector(const Vector &other) : arr_(nullptr), size_(0),
		                              capacity_(0),  alloc_(Allocator()) {
			arr_ = copyVector(other.arr_, other.size_, other.capacity_);
			size_ = other.size_;
			capacity_ = other.capacity_;
		};

		size_type
		size() const { return size_; };

		size_type
		capacity() const { return capacity_; };

		void
		reserve(size_type new_cap) {
			if (new_cap < capacity_)
				return;
			value_type *new_arr = copyVector(arr_, size_, new_cap);
			cleanVector();
			arr_ = new_arr;
			size_ = std::min(new_cap, size_);
			capacity_ = new_cap;
		};

		void
		resize(size_type count, value_type value = T()) {
			value_type *new_arr = copyVector(arr_, size_, count);
			if (count > size_) {
				try {
					fillVector(new_arr + size_, count - size_, value);
				} catch (...) {
					alloc_.deallocate(new_arr, count);
					throw;
				}
			}
			cleanVector();
			arr_ = new_arr;
			size_ = count;
			capacity_ = count;
		};

		void
		push_back(const_reference value) { // нестрогая гарантия! должна быть строгая
			if (capacity_ == size_)
				reserve(2 * capacity_);
			alloc_.construct(&arr_[size_], value); // не понятно, нужен все-таки адрес или объект // placement new?
			size_++;
			capacity_ *= 2;
		};

		void
		pop_back() {
			--size_;
			alloc_.destroy(&(arr_[size_])); // не понятно, нужен все-таки адрес или объект
		};

		reference
		operator[](size_t i) { return arr_[i]; };

		const_reference
		operator[](size_t i) const { return arr_[i]; };

		reference
		at(size_type i) {
			if (i > size_)
				throw std::out_of_range("...");
			return arr_[i];
		}

		Vector&
		operator=(const Vector& other) {
			if (this == &other)
				return *this;
			value_type *new_arr = copyVector(other.arr_, other.size_, other.capacity_);
			cleanVector();
			arr_ = new_arr;
			size_ = other.size_;
			capacity_ = other.capacity_;
			return *this;
		};

		void
		clear() {
			for (size_type i = 0; i < size_; ++i)
				alloc_.destroy(&(arr_[i]));
			size_ = 0;
		};

		void
		assign(size_type count, const_reference value) {
			value_type *new_arr = initVector(count);
			try {
				fillVector(new_arr, count, value);
			} catch (...) {
				alloc_.deallocate(new_arr, count);
				throw;
			}
			cleanVector();
			arr_ = new_arr;
			size_ = count;
			capacity_ = count;
		}

		bool
		empty() const {
			if (size_ == 0)
				return true;
			return false;
		}

		allocator_type
		get_allocator() const { return alloc_; }

//		template< class InputIt >
//		void assign( InputIt first, InputIt last );
		/*iterator erase(iterator pos) { // нестрогая гарантия! должна быть строгая
			alloc_.destroy(*pos);
			for (pos; pos != this.end(); ++pos)
				*pos = *pos + 1;
		};*/
//	iterator erase(iterator first, iterator last) {};
		~Vector() { cleanVector(); };
	};

};
// переделать copyVector на строгую гарантию и 2 входных параметра

#endif
