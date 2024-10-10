#include <iostream>
#include <stdexcept>

template <typename T>
class LinearList
{
public:
    virtual ~LinearList() {};
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
protected:
    int currentSize;
    int capacity;
    T *arr;

public:
    ArrayList(int len)
    {
        if (len < 1)
        {
            throw std::invalid_argument("illegalParameterValue");
        }
        this->capacity = len;
        this->currentSize = 0;
        arr = new T[capacity];
    }

    ~ArrayList()
    {
        delete[] arr;
    }

    bool isEmpty() const override
    {
        return this->currentSize == 0;
    }

    int size() const override
    {
        return this->currentSize;
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

    void insert(int index, const T &element) override
    {
        if (index < 0 || index > currentSize)
        {
            throw std::out_of_range("Index out of range");
        }
        if (currentSize == capacity)
        {
            throw std::overflow_error("List is full");
        }
        for (int i = currentSize; i > index; --i)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = element;
        ++currentSize;
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
        ArrayList<int> list(10);
        list.insert(0, 1);
        list.insert(1, 2);
        list.insert(2, 3);
        list.output(std::cout);
        list.erase(1);
        list.output(std::cout);
        std::cout << "Element at index 1: " << list.get(1) << std::endl;
        std::cout << "Index of element 3: " << list.indexOf(3) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
