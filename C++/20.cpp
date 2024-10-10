#include <stdexcept>
#include "20.h"
unsigned long long fibonacci(unsigned long n) 
{
	const unsigned long num0 = 1;
	const unsigned long num1 = 1;
	if (n == 0) {
		throw std::invalid_argument("²ÎÊıÓĞÎó");
	}
	if (n == 1) {
		return static_cast<unsigned long long>(num0);
	}
	if (n == 2) {
		return static_cast<unsigned long long>(num0) + num1;
	}
	if (n > 2) {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}
