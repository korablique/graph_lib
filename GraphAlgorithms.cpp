#include "GraphAlgorithms.h"

size_t dfsImpl(
        const size_t node_index,
        std::map<size_t, bool>& visited,
        const std::vector<std::vector<size_t>>& adjacency_list) {
    size_t visited_vertices = 1;
    visited[node_index] = true;
    for (auto& v : adjacency_list[node_index]) {
        if (!visited[v]) {
            visited_vertices += dfsImpl(v, visited, adjacency_list);
        }
    }
    return visited_vertices;
}

size_t dfs(const std::vector<std::vector<size_t>>& adjacency_list) {
    std::map<size_t, bool> visited;
    for (auto index = 0; index < adjacency_list.size(); ++index) {
        visited.insert({index, false});
    }
    return dfsImpl(0, visited, adjacency_list);
}

void dfsForConnectedComponentsImpl(
        size_t node_index,
        std::map<size_t, bool>& visited,
        const std::vector<std::vector<size_t>>& adjacency_list,
        std::vector<size_t>& connected_component) {
    visited[node_index] = true;
    connected_component.push_back(node_index);
    for (auto& v : adjacency_list[node_index]) {
        if (!visited[v]) {
            dfsForConnectedComponentsImpl(v, visited, adjacency_list, connected_component);
        }
    }
}
