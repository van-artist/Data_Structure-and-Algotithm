#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedQueue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &element) : data(element), next(nullptr) {}
    };

    Node *frontNode;
    Node *backNode;
    int count;

public:
    LinkedQueue() : frontNode(nullptr), backNode(nullptr), count(0) {}

    ~LinkedQueue()
    {
        while (!empty())
        {
            pop();
        }
    }

    bool empty() const
    {
        return count == 0;
    }

    int size() const
    {
        return count;
    }

    T &front()
    {
        if (empty())
        {
            throw std::underflow_error("Queue is empty");
        }
        return frontNode->data;
    }

    T &back()
    {
        if (empty())
        {
            throw std::underflow_error("Queue is empty");
        }
        return backNode->data;
    }

    void push(const T &element)
    {
        Node *newNode = new Node(element);
        if (empty())
        {
            frontNode = backNode = newNode;
        }
        else
        {
            backNode->next = newNode;
            backNode = newNode;
        }
        ++count;
    }

    void pop()
    {
        if (empty())
        {
            throw std::underflow_error("Queue is empty");
        }
        Node *oldFront = frontNode;
        frontNode = frontNode->next;
        delete oldFront;
        --count;
        if (empty()) // If queue becomes empty, reset backNode as well
        {
            backNode = nullptr;
        }
    }
};

int main()
{
    try
    {
        LinkedQueue<int> q;
        q.push(10);
        q.push(20);
        q.push(30);

        std::cout << "Front element: " << q.front() << std::endl;
        std::cout << "Back element: " << q.back() << std::endl;

        q.pop();
        std::cout << "Front element after pop: " << q.front() << std::endl;
        std::cout << "Queue size: " << q.size() << std::endl;

        q.pop();
        q.pop();

        std::cout << "Queue is empty: " << std::boolalpha << q.empty() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
