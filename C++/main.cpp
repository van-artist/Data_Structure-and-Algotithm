#include <iostream>
#include "19.h"
#include "20.h"
#include "21.cpp"
#include "22.cpp"
int main() {
	auto result = factorial(10);
	std::cout << result << std::endl;
	auto result20 = fibonacci(10);
	std::cout << result20 << std::endl;
	auto result21 = fun21(7);
	std::cout << result21 << std::endl;
	auto result22 = ackerman(9, 6);
	std::cout << result22 << std::endl;
	return 0;
}
 