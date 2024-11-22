#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP
#include <iostream>
#include <vector>
using namespace std;

class UnionFind
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int size) : parent(size), rank(size, 0)
    {
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX] += 1;
            }
        }
    }

    bool isConnected(int x, int y)
    {
        return find(x) == find(y);
    }
};

#endif // UNION_FIND_HPP