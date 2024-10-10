#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class LinearList
{
public:
    virtual ~LinearList() {}
    virtual bool isEmpty() const = 0;
    virtual int size() const = 0;
    virtual T &get(int index) const = 0;
    virtual int indexOf(const T &element) const = 0;
    virtual void erase(int index) = 0;
    virtual void insert(int index, const T &element) = 0;
    virtual void output(std::ostream &out) const = 0;
};

template <typename T>
class ArrayList : public LinearList<T>
{
private:
    int currentSize;
    int capacity;
    int enlargeMode;
    int enlargeSize;
    T *arr;

    void enlargeArr()
    {
        T *newArr = nullptr;
        switch (enlargeMode)
        {
        case 0:
            newArr = new T[capacity * 2];
            break;
        case 1:
            newArr = new T[capacity + enlargeSize];
            break;
        default:
            throw std::logic_error("Invalid enlarge mode");
        }
        std::copy(arr, arr + capacity, newArr);
        delete[] arr;
        arr = newArr;
        capacity = (enlargeMode == 0) ? capacity * 2 : capacity + enlargeSize;
    }

public:
    friend class ArrayList;

    ArrayList(int len)
    {
        if (len < 1)
        {
            throw std::invalid_argument("illegalParameterValue");
        }
        capacity = len;
        currentSize = 0;
        arr = new T[capacity];
        enlargeMode = 0;
        enlargeSize = 0;
    }

    ArrayList(int len, int enlargeSize)
    {
        if (len < 1)
        {
            throw std::invalid_argument("illegalParameterValue");
        }
        capacity = len;
        currentSize = 0;
        arr = new T[capacity];
        enlargeMode = 1;
        this->enlargeSize = enlargeSize;
    }

    ~ArrayList()
    {
        delete[] arr;
    }

    bool isEmpty() const override
    {
        return currentSize == 0;
    }

    int size() const override
    {
        return currentSize;
    }

    T &get(int index) const override
    {
        if (index < 0 || index >= currentSize)
        {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    int indexOf(const T &element) const override
    {
        for (int i = 0; i < currentSize; i++)
        {
            if (arr[i] == element)
            {
                return i;
            }
        }
        return -1;
    }

    int lastIndexOf(const T &element) const
    {
        for (int i = currentSize - 1; i >= 0; i--)
        {
            if (arr[i] == element)
            {
                return i;
            }
        }
        return -1;
    }

    void erase(int index) override
    {
        if (index < 0 || index >= currentSize)
        {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < currentSize - 1; ++i)
        {
            arr[i] = arr[i + 1];
        }
        --currentSize;
    }

    void removeRange(int start, int end)
    {
        if (start < 0 || end >= currentSize || start > end)
        {
            throw std::out_of_range("Index out of range");
        }
        int rangeSize = end - start + 1;
        for (int i = start; i < currentSize - rangeSize; ++i)
        {
            arr[i] = arr[i + rangeSize];
        }
        currentSize -= rangeSize;
    }

    void insert(int index, const T &element) override
    {
        if (index < 0 || index > currentSize)
        {
            throw std::out_of_range("Index out of range");
        }
        if (currentSize == capacity)
        {
            enlargeArr();
        }
        for (int i = currentSize; i > index; --i)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = element;
        ++currentSize;
    }

    void push_back(const T &element)
    {
        if (currentSize == capacity)
        {
            enlargeArr();
        }
        arr[currentSize++] = element;
    }

    void pop_back()
    {
        if (currentSize == 0)
        {
            throw std::out_of_range("ArrayList is empty");
        }
        --currentSize;
    }

    void reverse()
    {
        int left = 0;
        int right = currentSize - 1;
        while (left < right)
        {
            std::swap(arr[left], arr[right]);
            ++left;
            --right;
        }
    }

    void clear()
    {
        currentSize = 0;
    }

    void set(int index, const T &element)
    {
        if (index < 0 || index >= currentSize)
        {
            throw std::out_of_range("Index out of range");
        }
        arr[index] = element;
    }

    bool operator==(const ArrayList &other) const
    {
        if (this->currentSize != other.currentSize)
        {
            return false;
        }
        for (int i = 0; i < currentSize; ++i)
        {
            if (arr[i] != other.arr[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator<(const ArrayList &other) const
    {
        int minSize = std::min(this->currentSize, other.currentSize);
        for (int i = 0; i < minSize; ++i)
        {
            if (arr[i] < other.arr[i])
            {
                return true;
            }
            if (arr[i] > other.arr[i])
            {
                return false;
            }
        }
        return this->currentSize < other.currentSize;
    }

    void output(std::ostream &out) const override
    {
        for (int i = 0; i < currentSize; ++i)
        {
            out << arr[i] << " ";
        }
        out << std::endl;
    }
};

int main()
{
    try
    {
        ArrayList<int> list1(10);
        list1.push_back(1);
        list1.push_back(2);
        list1.push_back(3);
        list1.push_back(4);
        list1.push_back(5);

        std::cout << "Original list:" << std::endl;
        list1.output(std::cout);

        list1.reverse();
        std::cout << "Reversed list:" << std::endl;
        list1.output(std::cout);

        list1.set(2, 99);
        std::cout << "After setting index 2 to 99:" << std::endl;
        list1.output(std::cout);

        std::cout << "Index of element 99: " << list1.indexOf(99) << std::endl;
        std::cout << "Last index of element 99: " << list1.lastIndexOf(99) << std::endl;

        list1.removeRange(1, 3);
        std::cout << "After removing range from index 1 to 3:" << std::endl;
        list1.output(std::cout);

        list1.clear();
        std::cout << "After clearing the list:" << std::endl;
        list1.output(std::cout);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
