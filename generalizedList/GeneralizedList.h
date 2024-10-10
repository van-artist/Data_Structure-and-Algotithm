#ifndef GENERALIZEDLIST_H
#define GENERALIZEDLIST_H

#include <vector>
#include <variant>

using GeneralizedElemenType = std::variant<int, char, std::string, std::shared_ptr<class GeneralizedList>>;

class GeneralizedList
{
private:
    std::vector<GeneralizedElemenType> elements;

public:
    GeneralizedList(/* args */);
    ~GeneralizedList();
};

GeneralizedList::GeneralizedList(/* args */)
{
}

GeneralizedList::~GeneralizedList()
{
}

#endif // GENERALIZEDLIST_H