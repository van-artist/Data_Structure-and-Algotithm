#include <iostream>

template <typename T>
class Queue
{
public:
    virtual ~Queue() = 0; // 纯虚析构函数需要一个定义
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual T &front() = 0;
    virtual T &back() = 0;
    virtual T &pop() = 0;
    virtual void push(const T &element) = 0;
};

// 定义纯虚函数的实现
template <typename T>
Queue<T>::~Queue() {}

template <typename T>
class ArrayQueue : public Queue<T>
{
public:
    ArrayQueue(int queueSize);
    ~ArrayQueue();
    void push(const T &element);
    T &pop();
    T &front();
    T &back();
    bool empty();
    int size();

private:
    int queueSize = 0;
    int queueFront = 0;
    int queueBack = 0;
    int count = 0; // 当前队列中的元素个数
    T *queue = nullptr;
};

template <typename T>
ArrayQueue<T>::ArrayQueue(int queueSize)
{
    this->queueSize = queueSize;
    this->queue = new T[queueSize];
}

template <typename T>
ArrayQueue<T>::~ArrayQueue()
{
    delete[] queue;
}

template <typename T>
void ArrayQueue<T>::push(const T &element)
{
    if (count == queueSize)
    {
        throw std::overflow_error("Queue is full");
    }
    queue[queueBack] = element;
    queueBack = (queueBack + 1) % queueSize;
    ++count;
}

template <typename T>
T &ArrayQueue<T>::pop()
{
    if (empty())
    {
        throw std::underflow_error("Queue is empty");
    }
    T &frontElement = queue[queueFront];
    queueFront = (queueFront + 1) % queueSize;
    --count;
    return frontElement;
}

template <typename T>
bool ArrayQueue<T>::empty()
{
    return count == 0;
}

template <typename T>
int ArrayQueue<T>::size()
{
    return count;
}

template <typename T>
T &ArrayQueue<T>::front()
{
    if (empty())
    {
        throw std::underflow_error("Queue is empty");
    }
    return queue[queueFront];
}

template <typename T>
T &ArrayQueue<T>::back()
{
    if (empty())
    {
        throw std::underflow_error("Queue is empty");
    }
    return queue[(queueBack - 1 + queueSize) % queueSize];
}

int main()
{
    try
    {
        ArrayQueue<int> q(5);
        q.push(1);
        q.push(2);
        q.push(3);
        std::cout << "Front element: " << q.front() << std::endl;
        std::cout << "Back element: " << q.back() << std::endl;

        q.pop();
        std::cout << "Front element after pop: " << q.front() << std::endl;
        std::cout << "Queue size: " << q.size() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
