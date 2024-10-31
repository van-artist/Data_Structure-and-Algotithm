#ifndef THREADBINARYTREE_H
#define THREADBINARYTREE_H

template <typename T>
struct ThreadedNode
{
    bool ltag;
    bool rtag;
    ThreadedNode<T> *lchild;
    ThreadedNode<T> *rchild;
    ThreadedNode<T> *parent;
    ThreadedNode(bool ltag = false, bool rtag = false, ThreadedNode<T> *lchild = nullptr, ThreadedNode<T> *rchild = nullptr, ThreadedNode<T> *parent = nullptr) : rchild(rchild), lchild(lchild), rtag(rtag), ltag(ltag), parent(parent) {}
};

template <typename T>
class ThreadedBinaryTree
{
private:
public:
    ThreadedBinaryTree(/* args */);
    ~ThreadedBinaryTree();
};
template <typename T>
ThreadedBinaryTree<T>::ThreadedBinaryTree(/* args */)
{
}
template <typename T>
ThreadedBinaryTree<T>::~ThreadedBinaryTree()
{
}

#endif // THREADBINARYTREE_H