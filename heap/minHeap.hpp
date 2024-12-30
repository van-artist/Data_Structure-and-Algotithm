#include <vector>

template <typename T>
class minHeap
{
private:
    std::vector<T> heap;
    void heapify(std::vector<T> &arr, int index);
    int letf(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    int parent(int i) { return (i - 1) / 2; }

public:
    minHeap(const std::vector<T> &arr);
    ~minHeap();
};

template <typename T>
minHeap<T>::minHeap(const std::vector<T> &arr)
{
    for (const auto &i : arr)
    {
        heap.push_back(i);
    }
    heapify(heap);
}

template <typename T>
minHeap<T>::~minHeap()
{
}

template <typename T>
void minHeap<T>::heapify(std::vector<T> &arr, int index)
{
    int smallest_index = index;
    int left = this->left(index);
    int right = this->right(index);
}
