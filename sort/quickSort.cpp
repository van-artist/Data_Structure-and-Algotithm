#include <vector>

template <typename T, typename Interator>
void quickSort(std::vector<T> &arr, Interator begin, Interator end)
{
    if (begin >= end)
    {
        return;
    }
    Interator pivot = begin;
    Interator left = begin + 1;
    Interator right = end - 1;
    while (left <= right)
    {
        if (*left > *pivot && *right < *pivot)
        {
            std::swap(*left, *right);
        }
        if (*left <= *pivot)
        {
            left++;
        }
        if (*right >= *pivot)
        {
            right--;
        }
    }
    std::swap(*pivot, *right);
    quickSort(arr, begin, right);
    quickSort(arr, right + 1, end);
    return;
}
