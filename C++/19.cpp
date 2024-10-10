#include "19.h"
long long factorial(unsigned long n) 
{
	if (n == 1) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}