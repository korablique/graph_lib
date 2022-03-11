#ifndef GRAPH_LIB_GRAPHSREPRESENTATION_H
#define GRAPH_LIB_GRAPHSREPRESENTATION_H

#include <map>
#include <algorithm>
#include <numeric>

template <class T>
class Graph {
private:
    std::vector<T> m_nodes;
    std::vector<std::pair<T, T>> m_edges;
    std::vector<std::vector<bool>> m_adjacency_matrix;

    void setAdjacencyMatrix(std::vector<T> &nodes, std::vector<std::pair<T, T>> &edges);

    std::vector<std::vector<T>> getConnectedComponentsImpl(
            const std::vector<std::vector<size_t>>& adjacency_list,
            std::map<size_t, bool>& visited) const;

public:
    Graph(const std::vector<T> &nodes_list, const std::vector<std::pair<T, T>> &edges_list);
    explicit Graph(const std::vector<T> &nodes, const std::vector<std::vector<bool>> &adjacency_matrix);

    Graph<T>* buildCn(const std::vector<T> &nodes, size_t n);

    void addNode(const T& node);

    std::vector<std::vector<bool>> getAdjacencyMatrix() const;
    std::vector<T> getNodesList() const;
    std::vector<size_t> getDegreeList() const;
    std::vector<std::vector<size_t>> getAdjacencyList() const;
    bool isConnected() const;
    std::vector<std::vector<T>> getConnectedComponents() const;
    Graph<T> getComplementGraph() const;
};

#include "GraphsRepresentation.inl"

#endif //GRAPH_LIB_GRAPHSREPRESENTATION_H
