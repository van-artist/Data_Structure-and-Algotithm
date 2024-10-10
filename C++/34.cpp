#include <iostream>
#include <algorithm>
#include <iterator>

template <typename InputIt, typename T>
void fill(InputIt start, InputIt end, T value)
{
    for (; start != end; ++start)
    {
        *start = value;
    }
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
    fill(std::begin(arr), std::end(arr), 0);
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
