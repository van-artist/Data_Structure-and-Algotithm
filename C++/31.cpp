#include <algorithm>
#include <iostream>
#include <iterator>

template <typename T>
void permutations(T list[], int k, int m, bool isPrev = false)
{
    if (!isPrev)
    {
        std::sort(list + k, list + m + 1);
        do
        {
            std::copy(list + k, list + m + 1, std::ostream_iterator<T>(std::cout, " "));
            std::cout << std::endl;
        } while (std::next_permutation(list + k, list + m + 1));
    }
    else
    {
        std::sort(list + k, list + m + 1, std::greater<T>());
        do
        {
            std::copy(list + k, list + m + 1, std::ostream_iterator<T>(std::cout, " "));
            std::cout << std::endl;
        } while (std::prev_permutation(list + k, list + m + 1));
    }
}

int main()
{
    int *arr1 = new int[3]{1, 2, 3};
    int *arr2 = new int[3]{1, 2, 3};

    permutations(arr1, 0, 2);
    permutations(arr2, 0, 2, true);

    delete[] arr1; // 释放内存
    delete[] arr2; // 释放内存

    return 0;
}
