template <typename T>
bool isElementInArrayHelper(const T*arr[],int index,int size,const T&element) {
	if (index >= size) {
		return false;
	}
	if (element == arr[index]) {
		return true;
	}
	else {
		isElementInArrayHelper(arr, index + 1, size, element);
	}
}