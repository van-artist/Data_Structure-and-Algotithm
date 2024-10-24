#ifndef FULLBINARYTREE_H
#define FULLBINARYTREE_H
#include <iostream>
#include <vector>

template <typename T>
class FullBinaryTree
{
private:
    std::vector<T> tree; // 使用顺序表（vector）存储满二叉树

public:
    // 构造函数
    FullBinaryTree() {}

    // 插入节点
    void insert(const T &value)
    {
        tree.push_back(value);
    }

    // 获取左孩子节点的值
    T getLeftChild(int index) const
    {
        int leftChildIndex = 2 * index + 1;
        if (leftChildIndex < tree.size())
        {
            return tree[leftChildIndex];
        }
        throw std::out_of_range("左孩子不存在");
    }

    T getRightChild(int index) const
    {
        int rightChildIndex = 2 * index + 2;
        if (rightChildIndex < tree.size())
        {
            return tree[rightChildIndex];
        }
        throw std::out_of_range("右孩子不存在");
    }

    T getParent(int index) const
    {
        if (index == 0)
        {
            throw std::invalid_argument("根节点没有父节点");
        }
        int parentIndex = (index - 1) / 2;
        return tree[parentIndex];
    }

    void display() const
    {
        for (const auto &val : tree)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

#endif // FULLBINARYTREE_H