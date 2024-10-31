#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <queue>

template <typename T>
struct BinaryTreeNode
{
    T value;
    BinaryTreeNode *lchild;
    BinaryTreeNode *rchild;
    BinaryTreeNode *parent;
    BinaryTreeNode(const T &val) : value(val), lchild(nullptr), rchild(nullptr), parent(nullptr) {}
};

template <typename T>
using BinaryTreeNodePtr = BinaryTreeNode<T> *;

template <typename T>
class BinaryTree
{
private:
    BinaryTreeNodePtr<T> root;
    void deleteTree(BinaryTreeNodePtr<T> node);

public:
    BinaryTree() : root(nullptr) {}
    BinaryTree(BinaryTreeNodePtr<T> root) : root(root) {}
    BinaryTree(T value)
    {
        root = new BinaryTreeNode<T>(value);
    }
    ~BinaryTree() { deleteTree(root); }
    void setRoot(BinaryTreeNodePtr<T> root)
    {
        this->root = root;
    }
    T visit(BinaryTreeNodePtr<T> ptr) { return ptr->value; }
    void preOrderTraversal(BinaryTreeNodePtr<T> root, std::vector<T> &output) const;
    void inOrderTraversal(BinaryTreeNodePtr<T> root, std::vector<T> &output) const;
    void postOrderTraversal(BinaryTreeNodePtr<T> root, std::vector<T> &output) const;
    void levelOrderTraversal(BinaryTreeNodePtr<T> root, std::vector<T> &output) const;
};

template <typename T>
void BinaryTree<T>::deleteTree(BinaryTreeNodePtr<T> node)
{
    if (node != nullptr)
    {
        deleteTree(node->lchild);
        deleteTree(node->rchild);
        delete node;
    }
}

template <typename T>
void BinaryTree<T>::preOrderTraversal(BinaryTreeNodePtr<T> root, std::vector<T> &output) const
{
    if (root == nullptr)
        return;
    output.push_back(root->value);
    preOrderTraversal(root->lchild, output);
    preOrderTraversal(root->rchild, output);
}

template <typename T>
void BinaryTree<T>::inOrderTraversal(BinaryTreeNodePtr<T> root, std::vector<T> &output) const
{
    if (root == nullptr)
        return;
    inOrderTraversal(root->lchild, output);
    output.push_back(root->value);
    inOrderTraversal(root->rchild, output);
}

template <typename T>
void BinaryTree<T>::postOrderTraversal(BinaryTreeNodePtr<T> root, std::vector<T> &output) const
{
    if (root == nullptr)
        return;
    postOrderTraversal(root->lchild, output);
    postOrderTraversal(root->rchild, output);
    output.push_back(root->value);
}

template <typename T>
void BinaryTree<T>::levelOrderTraversal(BinaryTreeNodePtr<T> root, std::vector<T> &output) const
{
    if (root == nullptr)
        return;
    std::queue<BinaryTreeNodePtr<T>> node_queue;
    node_queue.push(root);
    while (!node_queue.empty())
    {
        BinaryTreeNodePtr<T> current_node_ptr = node_queue.front();
        node_queue.pop();
        output.push_back(current_node_ptr->value);
        if (current_node_ptr->lchild != nullptr)
        {
            node_queue.push(current_node_ptr->lchild);
        }
        if (current_node_ptr->rchild != nullptr)
        {
            node_queue.push(current_node_ptr->rchild);
        }
    }
}
#endif // BINARYTREE_H
