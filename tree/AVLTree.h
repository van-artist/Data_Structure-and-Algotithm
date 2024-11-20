#ifndef AVLTREE_H
#define AVLTREE_H

template <typename T>
struct AVLNode
{
    T data{};
    struct AVLNode *left{};
    struct AVLNode *right{};
    struct AVLNode *parent{};
    int height{};
    explicit TreeNode(T x) : val(x) {}
};
template <typename T>
int height(AVLNode<T> *node)
{
    if (node == nullptr)
    {
        node->height = 0;
        return 0;
    }
    return node->height;
}
template <typename T>
void updateHeight(AVLNode<T> *node)
{
    node->height = 1 + max(height(node->left), height(node->right));
}
template <typename T>
int balanceFactor(AVLNode<T> *node)
{
    return height(node->left) - height(node->right);
}
template <typename T>
class AVLTree
{
private:
    AVLNode<T> root;
    AVLNode<T> *find(const T data);
    void rotate_left(AVLNode<T> *node);
    void rotate_right(AVLNode<T> *node);
    void rotate_left_right(AVLNode<T> *node);
    void rotate_right_left(AVLNode<T> *node);
    void rotate(AVLNode<T> *node);
    AVLNode<T> *find_pre(AVLNode<T> *node);

public:
    void insert(T data);
    void remove(const T data);
    bool has(const T data);
    void update(T old_data, const T new_data);
};
template <typename T>
AVLNode<T> *AVLTree<T>::find_pre(AVLNode<T> *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->left == nullptr)
    {
        return nullptr;
    }
    AVLNode<T> *cur = node->left;
    while (cur->right != nullptr)
    {
        if (cur->right)
        {
            cur = cur->right;
            continue;
        }
        if (cur->left)
        {
            cur = cur->left;
            continue;
        }
    }
    return cur;
}
template <typename T>
AVLNode<T> *AVLTree<T>::find(const T data)
{
    AVLNode<T> *current_node = root;
    while (current_node != nullptr)
    {
        if (data < current_node->data)
        {
            current_node = current_node->left;
        }
        else if (data > current_node->data)
        {
            current_node = current_node->right;
        }
        else
        {
            return current_node;
        }
    }
}
template <typename T>
void AVLTree<T>::rotate_left(AVLNode<T> *node)
{
    AVLNode<T> *child = node->right;
    node->right = child->left;
    if (child->left != nullptr)
    {
        child->left->parent = node;
    }
    child->parent = node->parent;
    if (node->parent == nullptr)
    {
        this->root = child;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = child;
    }
    else
    {
        node->parent->right = child;
    }
    child->left = node;
    node->parent = child;
    updateHeight(node);
    updateHeight(child);
}

template <typename T>
void AVLTree<T>::rotate_right(AVLNode<T> *node)
{
    AVLNode<T> *child = node->left;
    node->left = child->right;
    if (child->right != nullptr)
    {
        child->right->parent = node;
    }
    child->parent = node->parent;
    if (node->parent == nullptr)
    {
        this->root = child;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = child;
    }
    else
    {
        node->parent->left = child;
    }
    child->right = node;
    node->parent = child;
    updateHeight(node);
    updateHeight(child);
}
template <typename T>
void AVLTree<T>::rotate_left_right(AVLNode<T> *node)
{
    rotate_left(node->left);
    rotate_right(node);
}

template <typename T>
void AVLTree<T>::rotate_right_left(AVLNode<T> *node)
{
    rotate_right(node->right);
    rotate_left(node);
}
template <typename T>
void AVLTree<T>::rotate(AVLNode<T> *node)
{
    if (balanceFactor(node) == 2)
    {
        if (balanceFactor(node->left) == -1)
        {
            rotate_left_right(node);
        }
        else
        {
            rotate_right(node);
        }
    }
    else if (balanceFactor(node) == -2)
    {
        if (balanceFactor(node->right) == 1)
        {
            rotate_right_left(node);
        }
        else
        {
            rotate_left(node);
        }
    }
}
template <typename T>
void AVLTree<T>::insert(T data)
{
    AVLNode<T> *new_node = new AVLNode<T>(data);
    AVLNode<T> *current_node = root;
    AVLNode<T> *parent_node = nullptr;
    while (current_node != nullptr)
    {
        parent_node = current_node;
        if (data < current_node->data)
        {
            current_node = current_node->left;
        }
        else if (data > current_node->data)
        {
            current_node = current_node->right;
        }
        else
        {
            return;
        }
    }
    new_node->parent = parent_node;
    if (parent_node == nullptr)
    {
        root = new_node;
    }
    else if (data < parent_node->data)
    {
        parent_node->left = new_node;
    }
    else
    {
        parent_node->right = new_node;
    }
    while (parent_node != nullptr)
    {
        updateHeight(parent_node);
        rotate(parent_node);
        parent_node = parent_node->parent;
    }
}
template <typename T>
void AVLTree<T>::remove(const T data)
{
    AVLNode<T> *target = this->find(data);
    if (target == nullptr)
    {
        return;
    }
    if (target->left == nullptr && target->right == nullptr)
    {
        target->parent->left = target->parent->right = nullptr;
        AVLNode<T> *cur = target->parent;
        delete target;
    }
}
template <typename T>
bool AVLTree<T>::has(const T data)
{
    return find(data) != nullptr;
}
template <typename T>
void AVLTree<T>::update(T old_data, const T new_data)
{
    AVLNode<T> target = this->find(old_data);
    target.data = new_data;
    return;
}

#endif // AVLTree_H
