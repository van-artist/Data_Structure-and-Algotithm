#include "MatrixGraph.hpp"
#include <iostream>

int main()
{
    // 创建一个无向图
    std::cout << "Testing undirected graph:" << std::endl;
    MatrixGraph<int> graph(5, false);

    // 添加边
    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 2, 1);
    graph.add_edge(1, 3, 1);
    graph.add_edge(2, 4, 1);

    // 打印邻接矩阵
    std::cout << "Adjacency matrix:" << std::endl;
    graph.print();

    // 验证边的存在性
    std::cout << "\nChecking edges:" << std::endl;
    std::cout << "Edge 0 -> 1: " << graph.has_edge(0, 1) << std::endl;
    std::cout << "Edge 3 -> 4: " << graph.has_edge(3, 4) << std::endl;

    // 深度优先遍历
    std::cout << "\nDFS traversal:" << std::endl;
    std::vector<bool> visited(graph.get_num_vertices(), false);
    graph.dfs(0, visited, [](int vertex)
              { std::cout << vertex << " "; });
    std::cout << std::endl;

    // 广度优先遍历
    std::cout << "\nBFS traversal:" << std::endl;
    visited.assign(graph.get_num_vertices(), false);
    graph.bfs(0, visited, [](int vertex)
              { std::cout << vertex << " "; });
    std::cout << std::endl;

    // 删除一条边并重新打印邻接矩阵
    graph.remove_edge(0, 1);
    std::cout << "\nAdjacency matrix after removing edge 0 -> 1:" << std::endl;
    graph.print();

    // 测试有向图
    std::cout << "\nTesting directed graph:" << std::endl;
    MatrixGraph<int> directedGraph(5, true);

    // 添加边
    directedGraph.add_edge(0, 1, 2);
    directedGraph.add_edge(1, 2, 3);
    directedGraph.add_edge(2, 3, 4);

    // 打印邻接矩阵
    std::cout << "\nAdjacency matrix for directed graph:" << std::endl;
    directedGraph.print();

    // 深度优先遍历
    std::cout << "\nDFS traversal for directed graph:" << std::endl;
    visited.assign(directedGraph.get_num_vertices(), false);
    directedGraph.dfs(0, visited, [](int vertex)
                      { std::cout << vertex << " "; });
    std::cout << std::endl;

    // 广度优先遍历
    std::cout << "\nBFS traversal for directed graph:" << std::endl;
    visited.assign(directedGraph.get_num_vertices(), false);
    directedGraph.bfs(0, visited, [](int vertex)
                      { std::cout << vertex << " "; });
    std::cout << std::endl;

    return 0;
}
