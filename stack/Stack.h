#ifndef STACK_H
#define STACK_H
template <typename T>
class Stack
{
private:
    T *elements;
    int stackSize;
    int stackTop;
    void resize(int newSize)
    {
        T *newElements = new T[newSize];
        for (int i = 0; i <= stackTop; ++i)
        {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        stackSize = newSize;
    }

public:
    Stack(int stackSize = 10)
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
            if (stackTop >= stackSize - 1)
            {
                resize(stackSize * 2);
            }
        }
        elements[++stackTop] = element;
    }
};

#endif // STACK_H