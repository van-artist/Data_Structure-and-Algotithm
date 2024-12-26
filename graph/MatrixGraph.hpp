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
    // std::vector<std::vector<int>> Floyd();
    bool is_eulerian_path_or_circuit();
    bool is_bridge(int fromVertex, int toVertex);
    void fleury(int startVertex);
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
template <typename T>
bool MatrixGraph<T>::is_eulerian_path_or_circuit()
{
    int oddCount = 0;
    for (int i = 0; i < matrix.size(); i++)
    {
        int degree = std::count_if(matrix[i].begin(), matrix[i].end(), [](T x)
                                   { return x != 0; });
        if (degree % 2 != 0)
        {
            oddCount++;
        }
    }
    return (oddCount == 0 || oddCount == 2); // 0 为欧拉回路，2 为欧拉路径
}

template <typename T>
bool MatrixGraph<T>::is_bridge(int fromVertex, int toVertex)
{
    // 复制当前图的邻接矩阵
    std::vector<std::vector<T>> tempMatrix = matrix;

    // 删除该边
    tempMatrix[fromVertex][toVertex] = 0;
    if (!directed)
    {
        tempMatrix[toVertex][fromVertex] = 0;
    }

    // 检查删除后是否仍然连通
    std::vector<bool> visited(matrix.size(), false);
    std::function<void(int)> dfs = [&](int vertex)
    {
        visited[vertex] = true;
        for (int i = 0; i < tempMatrix.size(); i++)
        {
            if (tempMatrix[vertex][i] != 0 && !visited[i])
            {
                dfs(i);
            }
        }
    };

    // 执行一次 DFS
    dfs(fromVertex);

    // 如果删除后有未访问的顶点，则是桥
    for (int i = 0; i < matrix.size(); i++)
    {
        if (std::count(tempMatrix[i].begin(), tempMatrix[i].end(), 0) != tempMatrix.size() && !visited[i])
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void MatrixGraph<T>::fleury(int startVertex)
{
    // 检查是否满足欧拉路径或回路条件
    if (!is_eulerian_path_or_circuit())
    {
        std::cout << "This graph does not have an Eulerian Path or Circuit." << std::endl;
        return;
    }

    // 使用栈来记录路径
    std::vector<int> path;
    std::function<void(int)> dfs = [&](int vertex)
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            if (matrix[vertex][i] != 0) // 如果有边
            {
                if (!is_bridge(vertex, i) || std::count_if(matrix[vertex].begin(), matrix[vertex].end(), [](T x)
                                                           { return x != 0; }) == 1)
                {
                    // 选择非桥边，或当此边是唯一可选边时，删除该边
                    remove_edge(vertex, i);
                    dfs(i);
                }
            }
        }
        path.push_back(vertex);
    };

    dfs(startVertex);

    // 输出结果路径
    std::reverse(path.begin(), path.end());
    for (int v : path)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}
#endif // MATRIX_GRAPH_H