#ifndef LIST_GRAPH_HPP
#define LIST_GRAPH_HPP
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <functional>
#include <algorithm>
#include "graph.hpp"

template <typename T>
class ListGraph : public Graph<T>
{
private:
    std::vector<std::list<std::pair<int, T>>> adjList;
    int edgeNums = 0;
    bool directed;

public:
    ListGraph(int numVertices, bool isDirected = false) : adjList(numVertices), directed(isDirected) {}

    void add_edge(int fromVertex, int toVertex, T weight) override;
    void remove_edge(int fromVertex, int toVertex) override;
    bool has_edge(int fromVertex, int toVertex) override;
    T get_edge(int fromVertex, int toVertex) override;
    std::vector<int> get_neighbors(int vertex) override;
    int get_num_vertices() override;
    int get_num_edges() override;
    void print() override;
    void dfs(int vertex, std::vector<bool> &visited, std::function<void(int)> func);
    void bfs(int vertex, std::vector<bool> &visited, std::function<void(int)> func);
};

template <typename T>
void ListGraph<T>::add_edge(int fromVertex, int toVertex, T weight)
{
    adjList[fromVertex].emplace_back(toVertex, weight);
    if (!directed)
    {
        adjList[toVertex].emplace_back(fromVertex, weight);
    }
    edgeNums++;
}

template <typename T>
void ListGraph<T>::remove_edge(int fromVertex, int toVertex)
{
    auto &edges = adjList[fromVertex];
    edges.remove_if([toVertex](const std::pair<int, T> &edge)
                    { return edge.first == toVertex; });
    if (!directed)
    {
        auto &revEdges = adjList[toVertex];
        revEdges.remove_if([fromVertex](const std::pair<int, T> &edge)
                           { return edge.first == fromVertex; });
    }
    edgeNums--;
}

template <typename T>
bool ListGraph<T>::has_edge(int fromVertex, int toVertex)
{
    for (const auto &edge : adjList[fromVertex])
    {
        if (edge.first == toVertex)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
T ListGraph<T>::get_edge(int fromVertex, int toVertex)
{
    for (const auto &edge : adjList[fromVertex])
    {
        if (edge.first == toVertex)
        {
            return edge.second;
        }
    }
    throw std::runtime_error("Edge does not exist");
}

template <typename T>
std::vector<int> ListGraph<T>::get_neighbors(int vertex)
{
    std::vector<int> neighbors;
    for (const auto &edge : adjList[vertex])
    {
        neighbors.push_back(edge.first);
    }
    return neighbors;
}

template <typename T>
int ListGraph<T>::get_num_vertices()
{
    return adjList.size();
}

template <typename T>
int ListGraph<T>::get_num_edges()
{
    return edgeNums;
}

template <typename T>
void ListGraph<T>::print()
{
    for (int i = 0; i < adjList.size(); i++)
    {
        std::cout << i << ": ";
        for (const auto &edge : adjList[i])
        {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void ListGraph<T>::dfs(int vertex, std::vector<bool> &visited, std::function<void(int)> func)
{
    visited[vertex] = true;
    func(vertex);
    for (const auto &edge : adjList[vertex])
    {
        if (!visited[edge.first])
        {
            dfs(edge.first, visited, func);
        }
    }
}

template <typename T>
void ListGraph<T>::bfs(int vertex, std::vector<bool> &visited, std::function<void(int)> func)
{
    std::queue<int> q;
    func(vertex);
    q.push(vertex);
    visited[vertex] = true;
    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        func(current);
        for (const auto &edge : adjList[current])
        {
            if (!visited[edge.first])
            {
                q.push(edge.first);
                visited[edge.first] = true;
            }
        }
    }
}

#endif // LIST_GRAPH_HPP
