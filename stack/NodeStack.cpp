#include <iostream>
#include <vector>
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
class Stack
{
private:
    ChainNode<T> *stackTop;
    int stackSize;

public:
    Stack()
    {
        stackTop = nullptr;
        stackSize = 0;
    }
    ~Stack()
    {
        ChainNode<T> currentNode = stackTop;
        while (currentNode != nullptr)
        {
            currentNode = stackTop;
            stackTop = currentNode->next;
            delete currentNode;
        }
    }
    void push(T element)
    {
        ChainNode<T> *newNode = new ChainNode<T>(element);
        newNode->next = stackTop;
        stackTop = newNode;
        stackSize++;
    }
    T pop()
    {
        ChainNode<T> tempNode = stackTop;
        stackTop = stackTop->next;
        delete tempNode;
        T element = peek();
        return peek;
    }
    T peek() const
    {
        return stackTop->element;
    }
    int size() { return stackSize; }
    bool empty() { return size == 0; }
};
int main()
{
    return 0;
}