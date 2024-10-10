#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <limits>

template <typename T>
class ChainNode
{
public:
    T element;
    ChainNode<T> *next;

    ChainNode(const T &element, ChainNode<T> *next = nullptr)
        : element(element), next(next) {}
};

template <typename T>
class Chain
{
protected:
    int listSize;
    ChainNode<T> *headNode;
    void checkIndex(int index) const;

public:
    Chain() : listSize(0), headNode(nullptr) {}
    Chain(const T &element) : listSize(1), headNode(new ChainNode<T>(element)) {}
    Chain(const Chain<T> &other);
    ~Chain();
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int index) const;
    int indexOf(const T &element) const;
    void erase(int index);
    void eraseElement(const T &element);
    void insert(int index, const T &element);
    void update(int index, const T &element);
    void output() const;
    void reverse();
    void binSort(int range);
    Chain<T> &operator=(const Chain<T> &other);

    class Iterator
    {
    private:
        ChainNode<T> *node;

    public:
        Iterator(ChainNode<T> *node = nullptr) : node(node) {}

        T &operator*() const { return node->element; }
        T *operator->() const { return &node->element; }

        Iterator &operator++()
        {
            node = node->next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            node = node->next;
            return temp;
        }

        bool operator==(const Iterator &other) const { return node == other.node; }
        bool operator!=(const Iterator &other) const { return node != other.node; }
    };

    Iterator begin() { return Iterator(headNode); }
    Iterator end() { return Iterator(nullptr); }
};
template <typename T>
Chain<T> &Chain<T>::operator=(const Chain<T> &other)
{
    if (this != &other) // 防止自我赋值
    {
        // 首先删除当前链表内容
        ChainNode<T> *currentNode = headNode;
        while (currentNode != nullptr)
        {
            ChainNode<T> *tempNode = currentNode;
            currentNode = currentNode->next;
            delete tempNode;
        }

        // 复制其他链表内容
        listSize = other.listSize;
        if (other.headNode != nullptr)
        {
            headNode = new ChainNode<T>(other.headNode->element);
            ChainNode<T> *currentNode = headNode;
            ChainNode<T> *otherCurrentNode = other.headNode->next;

            while (otherCurrentNode != nullptr)
            {
                currentNode->next = new ChainNode<T>(otherCurrentNode->element);
                currentNode = currentNode->next;
                otherCurrentNode = otherCurrentNode->next;
            }
        }
        else
        {
            headNode = nullptr;
        }
    }
    return *this;
}

template <typename T>
Chain<T>::Chain(const Chain<T> &other) : listSize(other.listSize), headNode(nullptr)
{
    if (other.headNode != nullptr)
    {
        headNode = new ChainNode<T>(other.headNode->element);
        ChainNode<T> *currentNode = headNode;
        ChainNode<T> *otherCurrentNode = other.headNode->next;

        while (otherCurrentNode != nullptr)
        {
            currentNode->next = new ChainNode<T>(otherCurrentNode->element);
            currentNode = currentNode->next;
            otherCurrentNode = otherCurrentNode->next;
        }
    }
}

template <typename T>
Chain<T>::~Chain()
{
    ChainNode<T> *currentNode = headNode;
    while (currentNode != nullptr)
    {
        ChainNode<T> *tempNode = currentNode;
        currentNode = currentNode->next;
        delete tempNode;
    }
}

template <typename T>
void Chain<T>::checkIndex(int index) const
{
    if (index < 0 || index >= listSize)
    {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
T &Chain<T>::get(int index) const
{
    checkIndex(index);
    ChainNode<T> *current = headNode;
    for (int i = 0; i < index; ++i)
    {
        current = current->next;
    }
    return current->element;
}

template <typename T>
int Chain<T>::indexOf(const T &element) const
{
    ChainNode<T> *currentNode = headNode;
    int resultIndex = 0;
    while (currentNode != nullptr)
    {
        if (currentNode->element == element)
        {
            return resultIndex;
        }
        currentNode = currentNode->next;
        ++resultIndex;
    }
    return -1; // 如果没有找到，返回 -1
}

template <typename T>
void Chain<T>::erase(int index)
{
    checkIndex(index);
    ChainNode<T> *currentNode = headNode;
    if (index == 0)
    {
        headNode = currentNode->next;
        delete currentNode;
    }
    else
    {
        ChainNode<T> *prevNode = nullptr;
        for (int i = 0; i < index; ++i)
        {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        prevNode->next = currentNode->next;
        delete currentNode;
    }
    --listSize;
}

template <typename T>
void Chain<T>::eraseElement(const T &element)
{
    ChainNode<T> *currentNode = headNode;
    ChainNode<T> *prevNode = nullptr;

    while (currentNode != nullptr)
    {
        if (currentNode->element == element)
        {
            if (prevNode == nullptr)
            {
                headNode = currentNode->next;
            }
            else
            {
                prevNode->next = currentNode->next;
            }
            delete currentNode;
            --listSize;
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

template <typename T>
void Chain<T>::insert(int index, const T &element)
{
    if (index < 0 || index > listSize)
    {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0)
    {
        headNode = new ChainNode<T>(element, headNode);
    }
    else
    {
        ChainNode<T> *current = headNode;
        for (int i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        current->next = new ChainNode<T>(element, current->next);
    }
    ++listSize;
}

template <typename T>
void Chain<T>::update(int index, const T &element)
{
    checkIndex(index);
    ChainNode<T> *current = headNode;
    for (int i = 0; i < index; ++i)
    {
        current = current->next;
    }
    current->element = element;
}

template <typename T>
void Chain<T>::output() const
{
    ChainNode<T> *currentNode = headNode;
    while (currentNode != nullptr)
    {
        std::cout << currentNode->element << " ";
        currentNode = currentNode->next;
    }
    std::cout << std::endl;
}
template <typename T>
void Chain<T>::reverse()
{
    ChainNode<T> *prevNode = nullptr;
    ChainNode<T> *currentNode = headNode;
    ChainNode<T> *nextNode = nullptr;

    while (currentNode != nullptr)
    {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    headNode = prevNode;
}

template <typename T>
void binSort(Chain<T> &chain, T minValue, T maxValue)
{
    int range = maxValue - minValue + 1;
    std::vector<Chain<T>> bins(range);

    auto current = chain.begin();
    while (current != chain.end())
    {
        T value = *current;
        bins[value - minValue].insert(0, value);
        ++current;
    }

    chain = Chain<T>();
    for (int i = 0; i < range; ++i)
    {
        auto binCurrent = bins[i].begin();
        while (binCurrent != bins[i].end())
        {
            chain.insert(chain.size(), *binCurrent);
            ++binCurrent;
        }
    }
}
template <typename T>
void Chain<T>::binSort(int range)
{
    ChainNode<T> **top = new ChainNode<T> *[range + 1];
    ChainNode<T> **bottom = new ChainNode<T> *[range + 1];
    for (int i = 0; i < range + 1; i++)
    {
        top[i] = bottom[i] = nullptr;
    }

    for (ChainNode<T> *currentNode = headNode; currentNode != nullptr; currentNode = currentNode->next)
    {
        auto element = currentNode->element;
        if (bottom[element] == nullptr)
        {
            bottom[element] = top[element] = currentNode;
        }
        else
        {
            top[element]->next = currentNode;
            top[element] = currentNode;
        }
    }

    ChainNode<T> *currentNode = nullptr;
    for (int i = 0; i < range + 1; ++i)
    {
        if (bottom[i] != nullptr)
        {
            if (currentNode == nullptr)
            {
                headNode = bottom[i];
            }
            else
            {
                currentNode->next = bottom[i];
            }
            currentNode = top[i];
        }
    }

    if (currentNode != nullptr)
    {
        currentNode->next = nullptr; // 确保链表末尾为空
    }

    delete[] top;
    delete[] bottom;
}
int main()
{
    Chain<int> chain;
    chain.insert(0, 10);
    chain.insert(1, 5);
    chain.insert(2, 20);
    chain.insert(3, 15);

    chain.output(); // 输出：10 5 20 15

    binSort(chain, 5, 20);
    chain.output(); // 输出：5 10 15 20

    return 0;
}
