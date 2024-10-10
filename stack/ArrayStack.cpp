#include <iostream>
#include <exception>
#include <stdexcept>

template <typename T>
class Stack
{
private:
    T *elements;
    int stackSize;
    int stackTop;

public:
    Stack(int stackSize)
    {
        if (stackSize <= 0)
        {
            throw std::invalid_argument("Stack size must be greater than 0");
        }
        this->stackSize = stackSize;
        stackTop = -1;
        elements = new T[stackSize];
    }

    ~Stack()
    {
        delete[] elements;
    }

    int size() const
    {
        return stackTop + 1;
    }

    bool isEmpty() const
    {
        return stackTop == -1;
    }

    T peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return elements[stackTop];
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }
        T result = elements[stackTop];
        --stackTop;
        return result;
    }

    void push(const T &element)
    {
        if (stackTop >= stackSize - 1)
        {
            throw std::out_of_range("Stack overflow");
        }
        elements[++stackTop] = element;
    }
};

int main()
{
    Stack<int> stack(5);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Top element: " << stack.peek() << std::endl;

    stack.pop();
    std::cout << "Top element after pop: " << stack.peek() << std::endl;

    return 0;
}
