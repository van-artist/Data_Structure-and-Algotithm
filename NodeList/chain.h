#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>
#include <stdexcept>

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
};

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
        nextNode = currentNode->next; // 保存下一个节点
        currentNode->next = prevNode; // 翻转当前节点的指针
        prevNode = currentNode;       // 移动 prevNode 到当前节点
        currentNode = nextNode;       // 移动 currentNode 到下一个节点
    }
    headNode = prevNode; // 更新头节点
}

#endif // CHAIN_H