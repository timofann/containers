#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP


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

}


#endif //TYPE_TRAITS_HPP
