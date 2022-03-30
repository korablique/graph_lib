#ifndef GRAPH_LIB_GRAPHALGORITHMS_H
#define GRAPH_LIB_GRAPHALGORITHMS_H

#include <cstddef>
#include <vector>
#include <map>

size_t dfs(const std::vector<std::vector<size_t>>& adjacency_list);

void dfsForConnectedComponentsImpl(
        size_t node_index,
        std::map<size_t, bool>& visited,
        const std::vector<std::vector<size_t>>& adjacency_list,
        std::vector<size_t>& connected_component);

#endif //GRAPH_LIB_GRAPHALGORITHMS_H
