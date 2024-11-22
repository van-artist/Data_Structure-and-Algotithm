#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <limits>
#include <functional>
#include "Graph.hpp"

template <typename T>
class MatrixGraph : public Graph<T>
{
private:
    using Edge = std::tuple<int, int, T>;
    std::vector<std::vector<T>> matrix;
    int edgeNums;
    bool directed;

public:
    MatrixGraph(int numVertices, bool isDirected = false)
        : matrix(numVertices, std::vector<T>(numVertices, 0)), directed(isDirected), edgeNums(0) {}
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
    std::vector<std::vector<int>> Floyd();
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
    int n = std::max({fromVertex, toVertex}) + 1;
    if (n > matrix.size())
    {
        matrix.resize(n, std::vector<T>(n, 0));
    }
    if (matrix[fromVertex][toVertex] == 0)
    {
        edgeNums++; // 增加边计数
    }
    matrix[fromVertex][toVertex] = weight;
    if (!directed)
    {
        matrix[toVertex][fromVertex] = weight;
    }
}

template <typename T>
void MatrixGraph<T>::remove_edge(int fromVertex, int toVertex)
{
    if (fromVertex < matrix.size() && toVertex < matrix.size() &&
        matrix[fromVertex][toVertex] != 0)
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
template <typename T>
std::vector<std::vector<int>> Floyd()
{
    std::vector<std::vector<int>> min_path_len(matrix.size(), std::vector<int>(matrix.size(), std::numeric_limits<int>::max()));
    for (int k = 0; k < matrix.size(); k++)
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                if (min_path_len[i][j] != 0)
                {
                    if (min_path_len[i][j] > min_path_len[i][k] + min_path_len[k][j])
                    {
                        min_path_len[i][j] = min_path_len[i][k] + min_path_len[k][j];
                    }
                }
            }
        }
    }
    return min_path_len;
}
#endif // MATRIX_GRAPH_H