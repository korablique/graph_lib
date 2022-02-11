#ifndef GRAPH_LIB_GRAPHSMETHODS_H
#define GRAPH_LIB_GRAPHSMETHODS_H

#include <vector>
#include <algorithm>

std::vector<size_t> getDegreeList(std::vector<std::vector<bool>>& adjacency_matrix);
std::vector<size_t> getDegreeList(std::vector<std::vector<double>>& adjacency_matrix);


#endif //GRAPH_LIB_GRAPHSMETHODS_H
