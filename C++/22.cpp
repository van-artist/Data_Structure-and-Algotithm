#include <cmath>
static unsigned long ackerman(unsigned int i,unsigned int j) {
	if (i == i && j >= 1) {
		return std::pow(i, j);
	}
	if (i >= 2 && j == 1) {
		return ackerman(i - 1, 2);
	}
	if (i >= 2 && j >= 2) {
		return ackerman(i - 1, ackerman(i, j - 1));
	}
}