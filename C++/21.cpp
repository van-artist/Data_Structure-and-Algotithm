static unsigned long fun21(unsigned int n) {
	if (n % 2 == 0) {
		return n / 2;
	}
	else {
		return fun21(3 * n + 1);
	}
}