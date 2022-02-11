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


