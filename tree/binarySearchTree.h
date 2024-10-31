#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <typename T>
struct BinaryTreeNode
{
    T value;
    T *lchild;
    T *rchild;
    T *parent;
    BinaryTreeNode(const T &val) : value(val), lchild(nullptr), rchild(nullptr), parent(nullptr) {}
};

template <typename T>
class BinarySearchTree
{
};
#endif // BINARYSEARCHTREE_H