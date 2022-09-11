#include <iostream>
#include <vector>
int main() {
	std::cout << "Hello, World!" << std::endl;
	std::vector<int> vec(0);
	std::cout << *(vec.begin()) << std::endl;
	return 0;
}
