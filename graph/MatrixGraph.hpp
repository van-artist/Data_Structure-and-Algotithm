#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <functional>
#include "graph.hpp"

template <typename T>
class MatrixGraph : public Graph<T>
{
private:
    std::vector<std::vector<T>> matrix;
    int edgeNums;
    bool directed;

public:
    MatrixGraph(int numVertices, bool isDirected = false) : matrix(numVertices, std::vector<T>(numVertices, 0)), directed(isDirected) {}
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
    ~MatrixGraph() {}
};

template <typename T>
void MatrixGraph<T>::dfs(int vertex, std::vector<bool> &visited, std::function<void(int)> func)
{
    visited[vertex] = true;
    func(vertex);
    for (int i = 0; i < matrix.size(); i++)
    {
        if (matrix[vertex][i] != 0 && !visited[i])
        {
            dfs(i, visited, func);
        }
    }
}

template <typename T>
void MatrixGraph<T>::bfs(int vertex, std::vector<bool> &visited, std::function<void(int)> func)
{
    std::queue<int> q;
    func(vertex);
    q.push(vertex);
    visited[vertex] = true;
    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        for (int i = 0; i < matrix.size(); i++)
        {
            if (matrix[current][i] != 0 && !visited[i])
            {
                func(i);
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

template <typename T>
void MatrixGraph<T>::add_edge(int fromVertex, int toVertex, T weight)
{
    int new_size = std::max(std::max(fromVertex, toVertex), edgeNums) + 1;
    if (matrix.size() < new_size)
    {
        matrix.resize(new_size);
        for (auto &row : matrix)
        {
            row.resize(new_size);
        }
    }
    matrix[fromVertex][toVertex] = weight;
    if (!directed)
    {
        matrix[toVertex][fromVertex] = weight;
    }
    edgeNums++;
}

template <typename T>
void MatrixGraph<T>::remove_edge(int fromVertex, int toVertex)
{
    if (matrix[fromVertex][toVertex] != 0)
    {
        matrix[fromVertex][toVertex] = 0;
        if (!directed)
        {
            matrix[toVertex][fromVertex] = 0;
        }
        edgeNums--;
    }
}
template <typename T>
bool MatrixGraph<T>::has_edge(int fromVertex, int toVertex)
{
    return matrix[fromVertex][toVertex] != 0;
}
template <typename T>
T MatrixGraph<T>::get_edge(int fromVertex, int toVertex)
{
    return matrix[fromVertex][toVertex];
}
template <typename T>
std::vector<int> MatrixGraph<T>::get_neighbors(int vertex)
{
    std::vector<int> neighbors;
    for (int i = 0; i < matrix.size(); i++)
    {
        if (matrix[vertex][i] != 0)
        {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}
template <typename T>
int MatrixGraph<T>::get_num_vertices()
{
    return matrix.size();
}
template <typename T>
int MatrixGraph<T>::get_num_edges()
{
    return edgeNums;
}
template <typename T>
void MatrixGraph<T>::print()
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

#endif // MATRIX_GRAPH_H