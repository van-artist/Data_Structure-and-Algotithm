#include <vector>

template <typename T>
void countinfSort(std::vector<T> &arr)
{
    auto n = arr.size();
    std::vector<T> result(n);
    T maxVal = *std::max_element(arr.begin(), arr.end());
    T minVal = *std::min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    std::vector<T> count(range, 0);
    for (int i = 0; i < n; i++)
    {
        count[arr[i] - minVal]++;
    }
    for (int i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        result[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = exp[i];
    }
    return;
}