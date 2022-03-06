#ifndef GRAPH_LIB_GRAPHSMETHODS_H
#define GRAPH_LIB_GRAPHSMETHODS_H

#include <vector>
#include <algorithm>

std::vector<size_t> getDegreeList(const std::vector<std::vector<bool>>& adjacency_matrix);
std::vector<size_t> getDegreeList(const std::vector<std::vector<double>>& adjacency_matrix);
bool isConnected(std::vector<int16_t>& nodes, const std::vector<std::vector<bool>>& adjacency_matrix);
std::vector<std::vector<int16_t>> getConnectedComponents(
        const std::vector<int16_t>& nodes, const std::vector<std::vector<bool>>& adjacency_matrix);

std::vector<std::vector<size_t>> getAdjacencyList(const std::vector<std::vector<bool>>& adjacency_matrix);

#endif //GRAPH_LIB_GRAPHSMETHODS_H
