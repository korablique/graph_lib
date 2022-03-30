#ifndef GRAPH_LIB_GRAPH_H
#define GRAPH_LIB_GRAPH_H

#include <map>
#include <algorithm>
#include <numeric>
#include "Node.h"

template <class T>
class Graph {
private:
    int64_t m_last_id = -1;
    std::vector<Node<T>> m_nodes;
    std::vector<std::pair<size_t, size_t>> m_edges;
    std::vector<std::vector<bool>> m_adjacency_matrix;

    Graph(const std::vector<Node<T>> nodes, const std::vector<std::vector<bool>> m_adjacency_matrix);

    void setNodesList(const std::vector<T> &nodes_data);
    void setEdgesList(const std::vector<std::vector<bool>> &adjacency_matrix);
    void setAdjacencyMatrix(std::vector<Node<T>> &nodes, std::vector<std::pair<size_t, size_t>> &edges);
    std::vector<std::vector<Node<T>>> getConnectedComponentsImpl(
            const std::vector<std::vector<size_t>>& adjacency_list,
            std::map<size_t, bool>& visited) const;

    Graph(const std::vector<T>& nodes_data, const std::vector<std::pair<size_t, size_t>>& edges_list);
    Graph(const std::vector<T> &nodes_data, const std::vector<std::vector<bool>> &adjacency_matrix);
public:
    static Graph<T> buildGraph(const std::vector<T>& nodes_data, const std::vector<std::pair<size_t, size_t>>& edges_list);
    static Graph<T> buildGraph(const std::vector<T>& nodes_data, const std::vector<std::vector<bool>>& adjacency_matrix);

    Graph<T>* buildCn(const std::vector<Node<T>> &nodes, size_t n);

    bool operator==(const Graph<T>& other) const;

    int64_t addNode(const T& node_data);
    void removeNode(int64_t id);
    void addEdge(int64_t idFirst, int64_t idSecond);
    void removeEdge(int64_t idFirst, int64_t idSecond);
    bool hasEdge(int64_t idFirst, int64_t idSecond);
    bool hasNode(int64_t id);

    std::vector<std::vector<bool>> getAdjacencyMatrix() const;
    std::vector<Node<T>> getNodesList() const;
    std::vector<std::pair<size_t, size_t>> getEdgesList() const;
    std::vector<size_t> getDegreeList() const;
    std::vector<std::vector<size_t>> getAdjacencyList() const;
    bool isConnected() const;
    std::vector<std::vector<Node<T>>> getConnectedComponents() const;
    Graph<T> getComplementGraph() const;
};

#include "Graph.inl"
#include "Node.inl"

#endif //GRAPH_LIB_GRAPH_H
