#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
std::vector<T> radixSort(std::vector<T> arr)
{
    T maxVal = *std::max_element(arr.begin(), arr.end());

    auto countingSort = [](std::vector<T> &arr, int exp)
    {
        int n = arr.size();
        std::vector<T> result(n);
        std::vector<int> count(10, 0);

        for (int i = 0; i < n; i++)
        {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }

        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--)
        {
            int digit = (arr[i] / exp) % 10;
            result[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        for (int i = 0; i < n; i++)
        {
            arr[i] = result[i];
        }
    };

    for (int exp = 1; maxVal / exp > 0; exp *= 10)
    {
        countingSort(arr, exp);
    }

    return arr;
}
