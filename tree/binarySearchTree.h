#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "binaryTree.h"

template <typename T>
class BinarySearchTree : public BinaryTree
{
    void insert(const T &elem);
};
template <typename T>
void BinarySearchTree<T>::insert(const T &elem)
{
}
#endif // BINARYSEARCHTREE_H
