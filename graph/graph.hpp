#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>

template <typename T>
class Graph
{
public:
    virtual void add_edge(int fromVertex, int toVertex, T weight) = 0;
    virtual void remove_edge(int fromVertex, int toVertex) = 0;
    virtual bool has_edge(int fromVertex, int toVertex) = 0;
    virtual T get_edge(int fromVertex, int toVertex) = 0;
    virtual std::vector<int> get_neighbors(int vertex) = 0;
    virtual int get_num_vertices() = 0;
    virtual int get_num_edges() = 0;
    virtual void print() = 0;
};

#endif // GRAPH_HPP