#include <iostream>
#include <algorithm>
#include <iterator>

template <typename T>
void permutations(T list[], int k, int m)
{
    std::sort(list + k, list + m + 1);
    do
    {
        std::copy(list + k, list + m + 1, std::ostream_iterator<T>(std::cout, " "));
        std::cout << std::endl;
    } while (std::next_permutation(list + k, list + m + 1));
}

int main()
{
    permutations<int>(new int[3]{1, 2, 3}, 0, 2);
    return 0;
}