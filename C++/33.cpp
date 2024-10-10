#include <iostream>
#include <algorithm>
#include <iterator>

template <typename InputIt, typename T>
long count(InputIt start, InputIt end, T value)
{
    long count = 0;
    for (; start != end + 1; ++start)
    {
        if (*start == value)
        {
            ++count;
        }
    }
    return count;
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
    int result = count(std::begin(arr), std::end(arr), 9);
    std::cout << result << std::endl;
    return 0;
}