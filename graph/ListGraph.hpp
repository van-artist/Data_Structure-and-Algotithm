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
        os << "(" << edge.from << ", " << edge.to << ", " << edge.weight << ")" << std::endl;
        return os;
    }
};

template <typename T, typename V>
class ListGraph : public Graph<T, V>
{
private:
    using EdgeType = Edge<T, V>;
    std::vector<std::list<EdgeType>> adjList;
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
    std::vector<T> dijkstra(const V &startVertex, std::vector<int> &prev);

public:
    ListGraph(int numVertices = 0, bool isDirected = false)
        : adjList(numVertices), directed(isDirected) {}
    void add_vertex(const V &vertex);
    void add_edge(const V &fromVertex, const V &toVertex, T weight) override;
    void remove_edge(const V &fromVertex, const V &toVertex) override;
    bool has_edge(const V &fromVertex, const V &toVertex) override;
    T get_edge(const V &fromVertex, const V &toVertex) override;
    std::vector<V> get_neighbors(const V &vertex) override;
    int get_num_vertices() override;
    int get_num_edges() override;
    void print() override;
    std::vector<EdgeType> findMST();
    std::vector<EdgeType> findMinPath(const V &startVertex, const V &endVertex);
    std::unordered_map<V, std::vector<typename ListGraph<T, V>::EdgeType>> findMinPath(const V &startVertex);
};
template <typename T, typename V>
void ListGraph<T, V>::add_vertex(const V &vertex)
{
    if (nodeIndex.find(vertex) == nodeIndex.end())
    {
        nodeIndex[vertex] = indexNode.size();
        indexNode.push_back(vertex);
        adjList.emplace_back(); // 添加新的邻接表
    }
}
template <typename T, typename V>
void ListGraph<T, V>::add_edge(const V &fromVertex, const V &toVertex, T weight)
{
    add_vertex(fromVertex);
    add_vertex(toVertex);
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

    adjList[fromIdx].remove_if([&](const EdgeType &edge)
                               { return edge.getFrom() == fromVertex && edge.getTo() == toVertex; });

    if (!directed)
    {
        adjList[toIdx].remove_if([&](const EdgeType &edge)
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
    for (const EdgeType &edge : adjList[fromIdx])
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
    for (const EdgeType &edge : adjList[idx])
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
    for (size_t i = 0; i < adjList.size(); i++)
    {
        std::cout << indexNode[i] << ": ";
        for (const EdgeType &edge : adjList[i])
        {
            std::cout << edge << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T, typename V>
std::vector<typename ListGraph<T, V>::EdgeType> ListGraph<T, V>::findMST()
{
    std::vector<EdgeType> result;
    UnionFind uf(get_num_vertices());
    std::vector<EdgeType> edges;

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
std::vector<T> ListGraph<T, V>::dijkstra(const V &startVertex, std::vector<int> &prev)
{
    int n = get_num_vertices();
    int startIdx = getNodeIndex(startVertex);

    std::vector<T> dist(n, std::numeric_limits<T>::max());
    prev.assign(n, -1);
    std::priority_queue<EdgeType, std::vector<EdgeType>, std::greater<EdgeType>> edge_pq;

    dist[startIdx] = 0;
    edge_pq.emplace(startVertex, startVertex, 0);

    while (!edge_pq.empty())
    {
        EdgeType cur_min_edge = edge_pq.top();
        edge_pq.pop();

        V current = cur_min_edge.getTo();
        int currentIdx = getNodeIndex(current);

        for (const EdgeType &edge : adjList[currentIdx])
        {
            V neighbor = edge.getTo();
            int neighborIdx = getNodeIndex(neighbor);
            T weight = edge.getWeight();

            if (dist[currentIdx] + weight < dist[neighborIdx])
            {
                dist[neighborIdx] = dist[currentIdx] + weight;
                prev[neighborIdx] = currentIdx;
                edge_pq.emplace(current, neighbor, dist[neighborIdx]);
            }
        }
    }

    return dist;
}

template <typename T, typename V>
std::unordered_map<V, std::vector<typename ListGraph<T, V>::EdgeType>>
ListGraph<T, V>::findMinPath(const V &startVertex)
{
    std::vector<int> prev;
    auto dist = dijkstra(startVertex, prev);

    std::unordered_map<V, std::vector<EdgeType>> allPaths;
    for (int i = 0; i < get_num_vertices(); ++i)
    {
        if (dist[i] == std::numeric_limits<T>::max())
            continue;

        std::vector<EdgeType> path;
        for (int v = i; prev[v] != -1; v = prev[v])
        {
            const EdgeType &edge = *std::find_if(adjList[prev[v]].begin(), adjList[prev[v]].end(),
                                                 [&](const EdgeType &e)
                                                 { return getNodeIndex(e.getTo()) == v; });
            path.push_back(edge);
        }
        std::reverse(path.begin(), path.end());
        allPaths[indexNode[i]] = path;
    }

    return allPaths;
}
template <typename T, typename V>
std::vector<typename ListGraph<T, V>::EdgeType>
ListGraph<T, V>::findMinPath(const V &startVertex, const V &endVertex)
{
    std::vector<int> prev;
    auto dist = dijkstra(startVertex, prev);

    int endIdx = getNodeIndex(endVertex);
    if (dist[endIdx] == std::numeric_limits<T>::max())
        return {};

    std::vector<EdgeType> path;
    for (int v = endIdx; prev[v] != -1; v = prev[v])
    {
        const EdgeType &edge = *std::find_if(adjList[prev[v]].begin(), adjList[prev[v]].end(),
                                             [&](const EdgeType &e)
                                             { return getNodeIndex(e.getTo()) == v; });
        path.push_back(edge);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

#endif // LIST_GRAPH_HPP
