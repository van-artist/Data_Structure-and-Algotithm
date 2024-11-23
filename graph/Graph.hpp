#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

template <typename T, typename V>
class Graph
{
public:
    virtual void add_edge(const V &fromVertex, const V &toVertex, T weight) = 0;
    virtual void remove_edge(const V &fromVertex, const V &toVertex) = 0;
    virtual bool has_edge(const V &fromVertex, const V &toVertex) = 0;
    virtual T get_edge(const V &fromVertex, const V &toVertex) = 0;
    virtual std::vector<V> get_neighbors(const V &vertex) = 0;
    virtual int get_num_vertices() = 0;
    virtual int get_num_edges() = 0;
    virtual void print() = 0;

    virtual ~Graph() = default;
};

#endif // GRAPH_HPP
