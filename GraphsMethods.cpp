#include <limits>
#include "GraphsMethods.h"

/// for undirected graphs
std::vector<size_t> getDegreeList(std::vector<std::vector<bool>>& adjacency_matrix) {
    // vertex degree = sum of 1 in the matrix row
    std::vector<size_t> degree_list(adjacency_matrix.size());
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        degree_list[i] = std::count(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), true);
    }
    std::sort(degree_list.rbegin(), degree_list.rend());   // reverse iterators
    return degree_list;
}

/// for undirected weighted graphs
std::vector<size_t> getDegreeList(std::vector<std::vector<double>>& adjacency_matrix) {
    std::vector<size_t> degree_list(adjacency_matrix.size());
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        // infinity means there is no such edge in the graph
        size_t elements_less_than_inf =
                std::count(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), std::numeric_limits<double>::max());
        degree_list[i] = adjacency_matrix.size() - elements_less_than_inf - 1; // minus the vertex for which the degree is calculated
    }
    std::sort(degree_list.rbegin(), degree_list.rend());   // reverse iterators
    return degree_list;
}

// TODO пока int вместо Node
std::vector<std::vector<int>> getAdjacencyList(std::vector<std::vector<bool>>& adjacency_matrix) {
    std::vector<std::vector<int>> adj_list(adjacency_matrix.size());
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        for (int j = 0; j < adjacency_matrix.size(); j++) {
            if (adjacency_matrix[i][j]) {
                adj_list[i].push_back(j);
            }
        }
    }
    return adj_list;
}

size_t dfsImpl(int node, std::vector<bool>& visited, std::vector<std::vector<int>> adjacency_list) {
    size_t visited_vertices = 1;
    visited[node] = true; // TODO сделать map
    for (auto v : adjacency_list[node]) { // TODO сделать ссылку
        if (!visited[v]) {
            visited_vertices += dfsImpl(v, visited, adjacency_list);
        }
    }
    return visited_vertices;
}

size_t dfs(int node, std::vector<std::vector<int>> adjacency_list) {
    std::vector<bool> visited(adjacency_list.size(), false);
    return dfsImpl(node, visited, adjacency_list);
}

bool isConnected(std::vector<std::vector<bool>>& adjacency_matrix) {
    auto adjacency_list = getAdjacencyList(adjacency_matrix);
    size_t vertices_reached = dfs(0, adjacency_list);
    return vertices_reached == adjacency_matrix.size();
}

