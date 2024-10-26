#ifndef LINKED_DICTIONARY_H
#define LINKED_DICTIONARY_H

#include <iostream>
#include <utility> // for std::pair
#include "Dictionary.h"

using namespace std;

// 节点结构，存储键值对
template <typename K, typename E>
struct ListNode
{
    pair<K, E> element; // 键值对
    ListNode<K, E> *next;

    ListNode(const pair<K, E> &thePair, ListNode<K, E> *n = nullptr)
        : element(thePair), next(n) {}
};

// 链表顺序表示的字典
template <typename K, typename E>
class LinkedDictionary : public Dictionary<K, E>
{
public:
    LinkedDictionary();                         // 构造函数
    ~LinkedDictionary();                        // 析构函数
    bool empty() const override;                // 判断字典是否为空
    int size() const override;                  // 返回字典中的元素个数
    pair<K, E> *find(const K &) const override; // 查找键对应的值
    void erase(const K &) override;             // 删除指定键的键值对
    void insert(const pair<K, E> &) override;   // 插入键值对

private:
    ListNode<K, E> *head; // 链表头指针
    int dSize;            // 字典中元素的数量
};

// 构造函数
template <typename K, typename E>
LinkedDictionary<K, E>::LinkedDictionary()
{
    head = nullptr;
    dSize = 0;
}

// 析构函数
template <typename K, typename E>
LinkedDictionary<K, E>::~LinkedDictionary()
{
    while (head != nullptr)
    {
        ListNode<K, E> *temp = head;
        head = head->next;
        delete temp;
    }
}

// 判断字典是否为空
template <typename K, typename E>
bool LinkedDictionary<K, E>::empty() const
{
    return dSize == 0;
}

// 返回字典的大小
template <typename K, typename E>
int LinkedDictionary<K, E>::size() const
{
    return dSize;
}

// 查找键值
template <typename K, typename E>
pair<K, E> *LinkedDictionary<K, E>::find(const K &key) const
{
    ListNode<K, E> *current = head;
    while (current != nullptr)
    {
        if (current->element.first == key)
        {
            return &current->element;
        }
        current = current->next;
    }
    return nullptr; // 未找到返回空指针
}

// 删除指定键的键值对
template <typename K, typename E>
void LinkedDictionary<K, E>::erase(const K &key)
{
    ListNode<K, E> *current = head;
    ListNode<K, E> *previous = nullptr;

    while (current != nullptr && current->element.first != key)
    {
        previous = current;
        current = current->next;
    }

    if (current != nullptr)
    {
        if (previous == nullptr)
        {
            // 删除头节点
            head = head->next;
        }
        else
        {
            // 删除中间或尾部节点
            previous->next = current->next;
        }
        delete current;
        --dSize;
    }
    else
    {
        cout << "Key not found." << endl;
    }
}

// 插入键值对
template <typename K, typename E>
void LinkedDictionary<K, E>::insert(const pair<K, E> &thePair)
{
    ListNode<K, E> *current = head;

    while (current != nullptr)
    {
        if (current->element.first == thePair.first)
        {
            // 如果键已经存在，更新它的值
            current->element.second = thePair.second;
            return;
        }
        current = current->next;
    }

    // 键不存在，插入新节点
    head = new ListNode<K, E>(thePair, head);
    ++dSize;
}

#endif // LINKED_DICTIONARY_H
