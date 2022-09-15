#include <iostream>
#include <vector>
//#include "test.hpp"
#include "iterators.hpp"
#include "vector.hpp"

int main() {
	ft::vector<std::string> x(6, "anna");
	x[1] = "toliy";
	x[2] = "anya";
	x[3] = "anytochka";
	x[4] = "bobah";
	x[5] = "bobka";
	ft::vector<std::string>::iterator it(&x[3]);
	*it = x[3];
//
	++it;
//
	std::cout << *it << std::endl;

//	int arr[6];
//	arr[0] = 1;
//	ft::InputIterator<false, int> it;
//	it = arr;
//	*it = 2;
//	std::cout << arr[0] << std::endl;
//	std::vector<int> vec(0);
//	std::cout << *(vec.begin()) << std::endl;
//	ft::pair<std::string, std::string> as("dgsh", "gf");
//	ft::pair<std::string, std::string> n(as);
//
//	int x = 1;
//	int y = 0;
//	std::cout << (x == y) << std::endl;
//	int vec[6];
//	vec[0] = 0;
//	vec[1] = 1;
//	vec[2] = 2;
//	vec[3] = 3;
//	vec[4] = 4;
//	vec[5] = 5;
//	int *p1 = vec;
//	int *p2 = &vec[5];
//
//	std::cout << p1 << " " << p2 << " " << p1 - p2 << std::endl;

//	std::vector<int> vec(6);
//	vec[0] = 0;
//	vec[1] = 1;
//	vec[2] = 2;
//	vec[3] = 3;
//	vec[4] = 4;
//	vec[5] = 5;
//	std::iterator_traits<std::input_iterator_tag> it1 = vec.end();
//	std::iterator_traits<std::input_iterator_tag> it2 = vec.begin();
//	std::cout << it1 << std::endl;








	return 0;
}
