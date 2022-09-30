#include <iostream>
#include <vector>
//#include "test.hpp"
//#include "iterators.hpp"
//#include "vector.hpp"
#include "iterators2.hpp"

int main() {
	std::string x[6];
//	ft::vector<std::string> x(6, "anna");
	x[0] = "anna";
	x[1] = "toliy";
	x[2] = "anya";
	x[3] = "anytochka";
	x[4] = "bobah";
	x[5] = "bobka";
//	ft::vector<std::string>::iterator it(&x[3]);
//	ft::Iterator<std::string> it(x);

/*
// проверка наследования операторов

	ft::InputIterator<false, std::string> it(x);
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;
	ft::InputIterator<false, std::string> it2(it);
	++it2;
	std::cout << *it << std::endl;
	std::cout << *it2 << std::endl;
	it2 = it;
	std::cout << *it2 << std::endl;

*/

/*
// проверка работы conditional

//	ft::InputIterator<false, std::string> it3(x);
//	std::cout << *it3 << std::endl;
//	*it3 = "annna";
//	std::cout << *it3 << std::endl;

	ft::InputIterator<true, std::string> it4(x); //error: cannot assign to variable 'a' with const-qualified type 'const int'
	std::cout << *it4 << std::endl;
	*it4 = "AnnA";
	std::cout << *it4 << std::endl;
*/

/*
// проверка доступа к родительским типам

	ft::InputIterator<false, std::string>::value_type hello("hello");
	std::cout << hello << std::endl;
*/


// проверка присвоения неконстантного итератора в константный

	std::vector<std::string> vec(5);
	vec[0] = "1";
	vec[1] = "2";
	vec[2] = "3";

//	std::vector<std::string>::const_iterator it6;
//	std::vector<std::string>::iterator it5;
//	std::vector<std::string>::iterator it9(it6);
//	std::vector<std::string>::const_iterator it10(it5);
//
//	ft::InputIterator<true, std::string> it6(x);
//	ft::InputIterator<false, std::string> it5(x);
//	ft::InputIterator<true, std::string> it9(it5); // не хочу ошибку тут
//	ft::InputIterator<false, std::string> it10(it6); // хочу ошибку здесь



/*
// проверка постинкрементации и операторов сравнения

	ft::InputIterator<false, std::string> it7(x);
	ft::InputIterator<false, std::string> it8(x);
	std::cout << (it7 == it8) << std::endl;
	std::cout << (it7 != it8) << std::endl;
	std::cout << *it7 << std::endl;
	std::cout << *it7++ << std::endl;
	std::cout << *it7 << std::endl;
	std::cout << (it7 == it8) << std::endl;
	std::cout << (it7 != it8) << std::endl;
*/

//	ft::Iterator<false, std::string, ft::input_iterator_tag> it11;
//	ft::Iterator<true, std::string, ft::input_iterator_tag> it12;
//	ft::Iterator<false, std::string, ft::input_iterator_tag> it13(it11);
//	ft::Iterator<true, std::string, ft::input_iterator_tag> it14(it12);
//	ft::Iterator<false, std::string, ft::input_iterator_tag> it15(it12); // не работать
//	ft::Iterator<true, std::string, ft::input_iterator_tag> it16(it11);



	return 0;
}
