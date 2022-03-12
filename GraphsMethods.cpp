#include <limits>
#include <unordered_map>
#include <cstdint>
#include "GraphsMethods.h"

/// for undirected graphs
std::vector<size_t> getDegreeList(const std::vector<std::vector<bool>>& adjacency_matrix) {
    // vertex degree = sum of 1 in the matrix row
    std::vector<size_t> degree_list(adjacency_matrix.size());
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        degree_list[i] = std::count(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), true);
    }
    std::sort(degree_list.rbegin(), degree_list.rend());   // reverse iterators
    return degree_list;
}

/// for undirected weighted graphs
std::vector<size_t> getDegreeList(const std::vector<std::vector<double>>& adjacency_matrix) {
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

/**
 * @param adjacency_matrix
 * @return list of nodes' indices
 */
std::vector<std::vector<size_t>> getAdjacencyList(const std::vector<std::vector<bool>>& adjacency_matrix) {
    std::vector<std::vector<size_t>> adj_list(adjacency_matrix.size());
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        for (int j = 0; j < adjacency_matrix.size(); j++) {
            if (adjacency_matrix[i][j]) {
                adj_list[i].push_back(j);
            }
        }
    }
    return adj_list;
}

// TODO replace all int16_t by Node
size_t dfsImpl(
        const int16_t node,
        std::unordered_map<int16_t, bool>& visited,
        const std::vector<std::vector<size_t>>& adjacency_list) {
    size_t visited_vertices = 1;
    visited[node] = true;
    for (auto& v : adjacency_list[node]) {
        if (!visited[v]) {
            visited_vertices += dfsImpl(v, visited, adjacency_list);
        }
    }
    return visited_vertices;
}

size_t dfs(const std::vector<int16_t>& nodes_list, const std::vector<std::vector<size_t>>& adjacency_list) {
    std::unordered_map<int16_t, bool> visited;
    for (auto& node : nodes_list) {
        visited.insert({node, false});
    }
    return dfsImpl(nodes_list[0], visited, adjacency_list);
}

void dfsForConnectedComponentsImpl(
        const int16_t node,
        std::unordered_map<int16_t, bool>& visited,
        const std::vector<std::vector<size_t>>& adjacency_list,
        std::vector<int16_t>& connected_component) {
    visited[node] = true;
    connected_component.push_back(node);
    for (auto& v : adjacency_list[node]) {
        if (!visited[v]) {
            dfsForConnectedComponentsImpl(v, visited, adjacency_list, connected_component);
        }
    }
}

std::vector<std::vector<int16_t>> getConnectedComponentsImpl(
        const std::vector<int16_t>& nodes_list,
        const std::vector<std::vector<size_t>>& adjacency_list,
        std::unordered_map<int16_t, bool>& visited) {
    std::vector<std::vector<int16_t>> components;
    auto remaining_nodes = nodes_list;
    std::vector<int16_t> current_component;
    while (!remaining_nodes.empty()) {
        dfsForConnectedComponentsImpl(remaining_nodes[0], visited, adjacency_list, current_component);
        components.push_back(current_component);
        for (auto item : current_component) {
            // remove() moves the elements to be removed to the end of vector
            // and returns the iterator to the first element to be removed.
            // erase() removes all elements from this iterator to remaining_nodes.end()
            remaining_nodes.erase(std::remove(
                    remaining_nodes.begin(), remaining_nodes.end(), item), remaining_nodes.end());
        }
        current_component.clear();
    }
    return components;
}

std::vector<std::vector<int16_t>> getConnectedComponents(
        const std::vector<int16_t>& nodes, const std::vector<std::vector<bool>>& adjacency_matrix) {
    auto adjacency_list = getAdjacencyList(adjacency_matrix);
    std::unordered_map<int16_t, bool> visited;
    for (auto& node : nodes) {
        visited.insert({node, false});
    }
    return getConnectedComponentsImpl(nodes, adjacency_list, visited);
}

bool isConnected(std::vector<int16_t>& nodes, const std::vector<std::vector<bool>>& adjacency_matrix) {
    auto adjacency_list = getAdjacencyList(adjacency_matrix);
    size_t vertices_reached = dfs(nodes, adjacency_list);
    return vertices_reached == adjacency_matrix.size();
}
