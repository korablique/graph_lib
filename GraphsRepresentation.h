#ifndef GRAPH_LIB_GRAPHSREPRESENTATION_H
#define GRAPH_LIB_GRAPHSREPRESENTATION_H

#include <map>
#include <algorithm>
#include <numeric>

template <class T1>
class Node {
private:
    T1 m_data;
public:
    explicit Node(T1 data): m_data(data){};
    bool operator==(const Node<T1>& other) const {
        return m_data == other.m_data;
    }
};

template <class T2>
class Graph{
private:
    std::vector<Node<T2>> m_nodes;
    std::vector<std::pair<Node<T2>, Node<T2>>> m_edges;
    std::vector<std::vector<bool>> m_adjacency_matrix;

    void setAdjacencyMatrix(std::vector<Node<T2>> &nodes, std::vector<std::pair<Node<T2>, Node<T2>>> &edges);

    std::vector<std::vector<Node<T2>>> getConnectedComponentsImpl(
            const std::vector<std::vector<size_t>>& adjacency_list,
            std::map<size_t, bool>& visited) const;

public:
    Graph(const std::vector<Node<T2>> &nodes_list, const std::vector<std::pair<Node<T2>, Node<T2>>> &edges_list);
    explicit Graph(const std::vector<Node<T2>> &nodes, const std::vector<std::vector<bool>> &adjacency_matrix);

    Graph<T2>* buildCn(const std::vector<Node<T2>> &nodes, size_t n);

    void addNode(Node<T2>& node);

    std::vector<std::vector<bool>> getAdjacencyMatrix() const;
    std::vector<Node<T2>> getNodesList() const;
    std::vector<size_t> getDegreeList() const;
    std::vector<std::vector<size_t>> getAdjacencyList() const;
    bool isConnected() const;
    std::vector<std::vector<Node<T2>>> getConnectedComponents() const;
    Graph<T2> getComplementGraph() const;
};

#include "GraphsRepresentation.inl"

#endif //GRAPH_LIB_GRAPHSREPRESENTATION_H
