#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <utility>

template <typename K, typename E>
class Dictionary
{
public:
    virtual ~Dictionary() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual pair<K, E> *find(const K &) const = 0;
    virtual void erase(const K &) = 0;
    virtual void insert(const pari<K, E> &) = 0;
};
#endif // DICTIONARY_H