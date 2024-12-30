#include "chain.h"
int main()
{
    Chain<int> chain;
    chain.insert(0, 10);
    chain.insert(1, 20);
    chain.insert(2, 30);

    chain.output(); // 输出：10 20 30

    chain.reverse();
    chain.output(); // 输出：30 20 10

    return 0;
}
