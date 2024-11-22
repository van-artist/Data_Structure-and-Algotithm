#ifndef LIST_GRAPH_HPP
#define LIST_GRAPH_HPP

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <functional>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include "Graph.hpp"
#include "UnionFind.hpp"

template <typename T, typename V>
class Edge
{
private:
    V from;
    V to;
    T weight;

public:
    Edge(V fromVertex, V toVertex, T weightValue)
        : from(fromVertex), to(toVertex), weight(weightValue) {}

    V getFrom() const { return from; }
    V getTo() const { return to; }
    T getWeight() const { return weight; }

    void setWeight(T weightValue) { weight = weightValue; }

    bool operator<(const Edge &other) const { return weight < other.weight; }
    bool operator>(const Edge &other) const { return weight > other.weight; }

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge)
    {
        os << "(" << edge.from << ", " << edge.to << ", " << edge.weight << ")";
        return os;
    }
};

template <typename T, typename V>
class ListGraph : public Graph<T>
{
private:
    using Edge = Edge<T, V>;
    std::vector<std::list<Edge>> adjList;
    int edgeNums = 0;
    bool directed;

    std::unordered_map<V, int> nodeIndex;
    std::vector<V> indexNode;

    int getNodeIndex(const V &node)
    {
        if (nodeIndex.find(node) == nodeIndex.end())
        {
            nodeIndex[node] = indexNode.size();
            indexNode.push_back(node);
        }
        return nodeIndex[node];
    }

public:
    ListGraph(int numVertices, bool isDirected = false)
        : adjList(numVertices), directed(isDirected) {}

    void add_edge(const V &fromVertex, const V &toVertex, T weight) override;
    void remove_edge(const V &fromVertex, const V &toVertex) override;
    bool has_edge(const V &fromVertex, const V &toVertex) override;
    T get_edge(const V &fromVertex, const V &toVertex) override;
    std::vector<V> get_neighbors(const V &vertex) override;
    int get_num_vertices() override;
    int get_num_edges() override;
    void print() override;
    std::vector<Edge> findMST();
    std::vector<Edge> findMinPath(const V &startVertex);
};

template <typename T, typename V>
void ListGraph<T, V>::add_edge(const V &fromVertex, const V &toVertex, T weight)
{
    int fromIdx = getNodeIndex(fromVertex);
    int toIdx = getNodeIndex(toVertex);

    adjList[fromIdx].emplace_back(fromVertex, toVertex, weight);
    if (!directed)
    {
        adjList[toIdx].emplace_back(toVertex, fromVertex, weight);
    }
    edgeNums++;
}

template <typename T, typename V>
void ListGraph<T, V>::remove_edge(const V &fromVertex, const V &toVertex)
{
    int fromIdx = getNodeIndex(fromVertex);
    int toIdx = getNodeIndex(toVertex);

    adjList[fromIdx].remove_if([&](const Edge &edge)
                               { return edge.getFrom() == fromVertex && edge.getTo() == toVertex; });

    if (!directed)
    {
        adjList[toIdx].remove_if([&](const Edge &edge)
                                 { return edge.getFrom() == toVertex && edge.getTo() == fromVertex; });
    }
    edgeNums--;
}

template <typename T, typename V>
bool ListGraph<T, V>::has_edge(const V &fromVertex, const V &toVertex)
{
    int fromIdx = getNodeIndex(fromVertex);
    for (const auto &edge : adjList[fromIdx])
    {
        if (edge.getTo() == toVertex)
        {
            return true;
        }
    }
    return false;
}

template <typename T, typename V>
T ListGraph<T, V>::get_edge(const V &fromVertex, const V &toVertex)
{
    int fromIdx = getNodeIndex(fromVertex);
    for (const Edge &edge : adjList[fromIdx])
    {
        if (edge.getTo() == toVertex)
        {
            return edge.getWeight();
        }
    }
    throw std::runtime_error("Edge does not exist");
}

template <typename T, typename V>
std::vector<V> ListGraph<T, V>::get_neighbors(const V &vertex)
{
    int idx = getNodeIndex(vertex);
    std::vector<V> neighbors;
    for (const Edge &edge : adjList[idx])
    {
        neighbors.push_back(edge.getTo());
    }
    return neighbors;
}

template <typename T, typename V>
int ListGraph<T, V>::get_num_vertices()
{
    return adjList.size();
}

template <typename T, typename V>
int ListGraph<T, V>::get_num_edges()
{
    return edgeNums;
}

template <typename T, typename V>
void ListGraph<T, V>::print()
{
    for (int i = 0; i < adjList.size(); i++)
    {
        std::cout << indexNode[i] << ": ";
        for (const Edge &edge : adjList[i])
        {
            std::cout << edge << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T, typename V>
std::vector<typename ListGraph<T, V>::Edge> ListGraph<T, V>::findMST()
{
    std::vector<Edge> result;
    UnionFind uf(get_num_vertices());
    std::vector<Edge> edges;

    for (const auto &edgeList : adjList)
    {
        for (const auto &edge : edgeList)
        {
            edges.push_back(edge);
        }
    }

    std::sort(edges.begin(), edges.end());

    for (const auto &edge : edges)
    {
        int fromIdx = getNodeIndex(edge.getFrom());
        int toIdx = getNodeIndex(edge.getTo());
        if (!uf.isConnected(fromIdx, toIdx))
        {
            uf.unionSets(fromIdx, toIdx);
            result.push_back(edge);
        }
    }
    return result;
}

template <typename T, typename V>
std::vector<typename ListGraph<T, V>::Edge> ListGraph<T, V>::findMinPath(const V &startVertex)
{
    int n = get_num_vertices();
    int startIdx = getNodeIndex(startVertex);

    std::vector<T> dist(n, std::numeric_limits<T>::max());
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edge_pq;
    dist[startIdx] = 0;
    edge_pq.emplace(startVertex, startVertex, 0);

    std::vector<Edge> result;

    while (!edge_pq.empty())
    {
        Edge cur_min_edge = edge_pq.top();
        edge_pq.pop();

        V current = cur_min_edge.getTo();
        int currentIdx = getNodeIndex(current);

        for (const Edge &edge : adjList[currentIdx])
        {
            V neighbor = edge.getTo();
            int neighborIdx = getNodeIndex(neighbor);
            T weight = edge.getWeight();

            if (dist[currentIdx] + weight < dist[neighborIdx])
            {
                dist[neighborIdx] = dist[currentIdx] + weight;
                edge_pq.emplace(current, neighbor, dist[neighborIdx]);
                result.push_back(Edge(startVertex, neighbor, dist[neighborIdx]));
            }
        }
    }
    return result;
}

#endif // LIST_GRAPH_HPP
