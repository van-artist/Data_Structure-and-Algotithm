#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T>
class LinearList
{
public:
    virtual ~LinearList() {}
    virtual bool isEmpty() const = 0;
    virtual int size() const = 0;
    virtual const T &get(int index) const = 0;
    virtual int indexOf(const T &element) const = 0;
    virtual void erase(int index) = 0;
    virtual void insert(int index, const T &element) = 0;
    virtual void output(std::ostream &out) const = 0;
};

template <typename T>
class ArrayList : public LinearList<T>
{
private:
    std::vector<T> arr;

public:
    class Iterator
    {
    private:
        typename std::vector<T>::iterator it;

    public:
        Iterator(typename std::vector<T>::iterator i) : it(i) {}

        T &operator*() const { return *it; }
        T *operator->() const { return &(*it); }

        Iterator &operator++()
        {
            ++it;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++it;
            return tmp;
        }

        Iterator &operator--()
        {
            --it;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --it;
            return tmp;
        }

        Iterator operator+(int n) const
        {
            return Iterator(it + n);
        }

        Iterator operator-(int n) const
        {
            return Iterator(it - n);
        }

        Iterator &operator+=(int n)
        {
            it += n;
            return *this;
        }

        Iterator &operator-=(int n)
        {
            it -= n;
            return *this;
        }

        T &operator[](int index)
        {
            return *(it + index);
        }

        bool operator==(const Iterator &other) const { return it == other.it; }
        bool operator!=(const Iterator &other) const { return it != other.it; }
        bool operator<(const Iterator &other) const { return it < other.it; }
        bool operator>(const Iterator &other) const { return it > other.it; }
        bool operator<=(const Iterator &other) const { return it <= other.it; }
        bool operator>=(const Iterator &other) const { return it >= other.it; }
    };

    ArrayList(int len)
    {
        if (len < 1)
        {
            throw std::invalid_argument("illegalParameterValue");
        }
        arr.reserve(len);
    }

    ~ArrayList() {}

    bool isEmpty() const override
    {
        return arr.empty();
    }

    int size() const override
    {
        return arr.size();
    }

    const T &get(int index) const override
    {
        if (index < 0 || static_cast<size_t>(index) >= arr.size())
        {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    int indexOf(const T &element) const override
    {
        auto it = std::find(arr.begin(), arr.end(), element);
        if (it != arr.end())
        {
            return std::distance(arr.begin(), it);
        }
        return -1;
    }

    void erase(int index) override
    {
        if (index < 0 || static_cast<size_t>(index) >= arr.size())
        {
            throw std::out_of_range("Index out of range");
        }
        arr.erase(arr.begin() + index);
    }

    void insert(int index, const T &element) override
    {
        if (index < 0 || static_cast<size_t>(index) > arr.size())
        {
            throw std::out_of_range("Index out of range");
        }
        arr.insert(arr.begin() + index, element);
    }

    void push_back(const T &element)
    {
        arr.push_back(element);
    }

    void pop_back()
    {
        if (arr.empty())
        {
            throw std::out_of_range("ArrayList is empty");
        }
        arr.pop_back();
    }

    Iterator begin()
    {
        return Iterator(arr.begin());
    }

    Iterator end()
    {
        return Iterator(arr.end());
    }

    void output(std::ostream &out) const override
    {
        for (const auto &elem : arr)
        {
            out << elem << " ";
        }
        out << std::endl;
    }
};

int main()
{
    ArrayList<int> list(10);
    for (int i = 0; i < 10; ++i)
    {
        list.push_back(i);
    }

    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    auto it = list.begin();
    it += 3;
    std::cout << "Element at index 3: " << *it << std::endl;

    return 0;
}
