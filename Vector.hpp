#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <cstdlib>
#include <vector>

template< class T, class Allocator = std::allocator<T> >
class Vector {
private:
	T* arr_;
	size_t size_;
	size_t capacity_;
	const Allocator &alloc_;
	void cleanVector() {
		for (size_type i = 0; i < size_; ++i)
			alloc_.destroy(&(arr_[i])); // не понятно, нужен все-таки адрес или объект
		alloc_.deallocate(arr_, capacity_);
	}
	void copyVector(const Vector &other) {
		capacity_ > 0 ? arr_ = alloc_.allocate(capacity_) : arr_ = nullptr;
		/*for (size_t i = 0; i < size_; ++i)
			alloc_.construct(&(arr_[i]), other[i]); // [i] на сколько сдвигает указатель? // не понятно, нужен все-таки адрес или объект
		 */
		if (arr_ == nullptr)
			return;
		try {
			std::uninitialized_copy(other.arr_, other.arr_ + other.size_, arr_); //вероятное увеличение времени работы из-за избегания перегружения оператора & (-> addresof)
		} catch (...) {
//			delete[] reinterpret_cast<int8_t*>(new_arr);
			alloc_.deallocate(arr_, capacity_);
			throw;
		}
	}
public:
//	typedef typename std::vector<T, Allocator>::iterator InputIt; // это не надо
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef typename std::vector<T, Allocator>::iterator iterator;
	typedef typename std::vector<T, Allocator>::const_iterator const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	Vector() : arr_(nullptr), size_(0), capacity_(0), alloc_(Allocator()) {};
	explicit Vector(const Allocator &alloc) : arr_(nullptr), size_(0), capacity_(0), alloc_(alloc) {};
	explicit Vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : size_(count), capacity_(count), alloc_(alloc) {
		capacity_ > 0 ? arr_ = alloc_.allocate(capacity_) : arr_ = nullptr;
		for (size_type i = 0; i < size_; ++i)
			alloc_.construct(&(arr_[i]), value); // [i] на сколько сдвигает указатель? // не понятно, нужен все-таки адрес или объект
	};
	template<class InputIt>
	Vector(InputIt first, InputIt last, const Allocator &alloc = Allocator()) : alloc_(alloc) {
		InputIt first2(first);
		size_ = 0;
		for (; first != last; ++first)
			++size_;
		capacity_ = size_;
		capacity_ > 0 ? arr_ = alloc_.allocate(capacity_) : arr_ = nullptr;
		for (size_type i = 0; i < size_; ++i)
			alloc_.construct(&(arr_[i]), *(first2 + i)); // [i] на сколько сдвигает указатель? // не понятно, нужен все-таки адрес или объект
	};
	Vector(const Vector &other) : size_(other.size_), capacity_(other.capacity_), alloc_(Allocator()) { copyVector(other); };
	size_type size() const { return size_; };
	size_type capacity() const { return capacity_; };
	void reserve(size_type new_cap) {
		T* new_arr;
		new_cap > 0 ? new_arr = alloc_.allocate(new_cap) : new_arr = nullptr; // моя версия
//		T* new_arr = reinterpret_cast<T*>(new int8_t[count * sizeof(T)]); // версия Мещерина
		if (new_cap > 0) {
			try {
				std::uninitialized_copy(arr_, arr_ + std::min(new_cap, size_), new_arr); //вероятное увеличение времени работы из-за избегания перегружения оператора & (-> addresof)
			} catch (...) {
//			delete[] reinterpret_cast<int8_t*>(new_arr);
				alloc_.deallocate(new_arr, new_cap);
				throw;
			}
		}
		/*size_t i = 0;
		try {
			for (; i < size_ && i < count; ++i)
				new(new_arr + i) T(arr_[i]);
//			    new_arr[i] = arr_[i]; // нельзя присвоить, потому что объект левого операнда не создан UB / segmentation fault
		} catch (...) {
			for (size_t j = 0; j < i; ++j) {
				(new_arr+j)->T();
			}
			delete[] reinterpret_cast<int8_t*>(new_arr);
			throw;
		}*/
		/*for (size_t k = 0; k < size_ && k < count; ++i)
			alloc_.destroy(&(arr_[k])); // по указателю передать ?
//			(arr_[k]->~T());
//		delete[] arr_; // вызовет деструкторы для объектов, которые еще не были созданы
//		delete[] reinterpret_cast<int8_t*>(arr_); // deallocate ?
		alloc_.deallocate(arr_, capacity_);*/
		cleanVector();
		arr_ = new_arr;
		size_ = std::min(new_cap, size_);
		capacity_ = new_cap;
	};
	void resize(size_type count, T value = T()) {
		T* new_arr;
		count > 0 ? new_arr = alloc_.allocate(count) : new_arr = nullptr; // моя версия
//		T* new_arr = reinterpret_cast<T*>(new int8_t[count * sizeof(T)]); // версия Мещерина
		if (count > 0) {
			try {
				std::uninitialized_copy(arr_, arr_ + std::min(count, size_), new_arr); //вероятное увеличение времени работы из-за избегания перегружения оператора & (-> addresof)
			} catch (...) {
//			delete[] reinterpret_cast<int8_t*>(new_arr);
				alloc_.deallocate(new_arr, count);
				throw;
			}
		}
		for (size_type i = size_; i < count; ++i)
			alloc_.construct(&(new_arr[i]), value); // [i] на сколько сдвигает указатель? // не понятно, нужен все-таки адрес или объект
//			new (arr_ + i) T(value);
		cleanVector();
		arr_ = new_arr;
		size_ = count;
		capacity_ = count;
	};
	void push_back(const T &value) { // нестрогая гарантия! должна быть строгая
		if (capacity_ == size_)
			reserve(2 * capacity_);
		/*try {
			std::uninitialized_copy(&value, &value, &(arr_[size_])); //вероятное увеличение времени работы из-за избегания перегружения оператора & (-> addresof)
		} catch (...) {
			throw;
		}*/ // есть ли смысл если при отлавливании исключения ничего не делаем
		alloc_.construct(&arr_[size_], value); // не понятно, нужен все-таки адрес или объект
//		new (arr_ + size_) T(value);
//		arr_[size_] = value;
		size_++;
		capacity_ *= 2;
	};
	void pop_back() {
		--size_;
		alloc_.destroy(&(arr_[size_])); // не понятно, нужен все-таки адрес или объект
//		(arr_ + size_)->~T();
	};
	T& operator[](size_t i) { return arr_[i]; };
	const T& operator[](size_t i) const { return arr_[i]; };
	T& at(size_type i) {
		if (i > size_)
			throw std::out_of_range("...");
		return arr_[i];
	}
	Vector& operator=(const Vector &other) { // нестрогая гарантия! должна быть строгая
		if (this == &other)
			return *this;
		cleanVector();
		size_ = other.size_;
		capacity_ = other.capacity_;
		copyVector(other);
		return *this;
	};
	void clear() {
		for (size_type i = 0; i < size_; ++i)
			alloc_.destroy(&(arr_[i]));
		size_ = 0;
	};
	/*iterator erase(iterator pos) { // нестрогая гарантия! должна быть строгая
		alloc_.destroy(*pos);
		for (pos; pos != this.end(); ++pos)
			*pos =
	};
	iterator erase(iterator first, iterator last) {};*/
	~Vector() { cleanVector(); };
};


// переделать copyVector на строгую гарантию и 2 входных параметра

#endif
