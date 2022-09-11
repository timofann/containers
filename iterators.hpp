#ifndef ITERATORS_HPP
#define ITERATORS_HPP

namespace ft {

	template <typename container>
	class InputIterator {
	public:
		 friend container;
	};


	class iterator {
	private:
		value_type *value_ptr_;
	public:
		reference operator*() { return *value_ptr_; };
	};

	class const_iterator {
	private:
		value_type *value_ptr_;
	public:
		const_reference operator*() { return *value_ptr_; };
	};


}

#endif
