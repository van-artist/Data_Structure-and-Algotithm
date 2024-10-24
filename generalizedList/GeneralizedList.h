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
    void pushElement(GeneralizedElemenType element)
    {
        elements.push_back(element);
    };
    void pushElement(int element)
    {
        elements.push_back(element);
    };
    void pushElement(char element)
    {
        elements.push_back(element);
    };
    void pushElement(std::string element)
    {
        elements.push_back(element);
    };
    void pushElement(std::shared_ptr<GeneralizedList> element)
    {
        elements.push_back(element);
    };
    GeneralizedElemenType getByIndex(int index)
    {
        return elements[index];
    }

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