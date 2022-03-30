#ifndef GRAPH_LIB_GRAPHSREPRESENTATION_H
#define GRAPH_LIB_GRAPHSREPRESENTATION_H

#include <map>
#include <algorithm>
#include <numeric>

template <class T1>
class Node {
private:
    int64_t m_id;
    T1 m_data;
public:
    Node(int64_t id, T1 data);
    bool operator==(const Node<T1>& other) const;

    int64_t getId() const;
    T1 getData() const;

    template <class T2>
    friend class Graph;
};

template <class T2>
class Graph {
private:
    int64_t m_last_id = -1;
    std::vector<Node<T2>> m_nodes;
    std::vector<std::pair<size_t, size_t>> m_edges;
    std::vector<std::vector<bool>> m_adjacency_matrix;

    Graph(const std::vector<Node<T2>> nodes, const std::vector<std::vector<bool>> m_adjacency_matrix);

    void setNodesList(const std::vector<T2> &nodes_data);
    void setEdgesList(const std::vector<std::vector<bool>> &adjacency_matrix);
    void setAdjacencyMatrix(std::vector<Node<T2>> &nodes, std::vector<std::pair<size_t, size_t>> &edges);
    std::vector<std::vector<Node<T2>>> getConnectedComponentsImpl(
            const std::vector<std::vector<size_t>>& adjacency_list,
            std::map<size_t, bool>& visited) const;

    Graph(const std::vector<T2>& nodes_data, const std::vector<std::pair<size_t, size_t>>& edges_list);

public:
    static Graph<T2> buildGraph(const std::vector<T2>& nodes_data, const std::vector<std::pair<size_t, size_t>>& edges_list);
    static Graph<T2> buildGraph(const std::vector<T2>& nodes_data, const std::vector<std::vector<bool>>& adjacency_matrix);

    Graph<T2>* buildCn(const std::vector<Node<T2>> &nodes, size_t n);

    bool operator==(const Graph<T2>& other) const;

    int64_t addNode(const T2& node_data);
    void removeNode(int64_t id);
    void addEdge(int64_t idFirst, int64_t idSecond);
    void removeEdge(int64_t idFirst, int64_t idSecond);
    bool hasEdge(int64_t idFirst, int64_t idSecond);
    bool hasNode(int64_t id);
    size_t getEdgesNumber();

    std::vector<std::vector<bool>> getAdjacencyMatrix() const;
    std::vector<Node<T2>> getNodesList() const;
    std::vector<std::pair<size_t, size_t>> getEdgesList() const;
    std::vector<size_t> getDegreeList() const;
    std::vector<std::vector<size_t>> getAdjacencyList() const;
    bool isConnected() const;
    std::vector<std::vector<Node<T2>>> getConnectedComponents() const;
    Graph<T2> getComplementGraph() const;

    Graph(const std::vector<T2> &nodes_data, const std::vector<std::vector<bool>> &adjacency_matrix);
};

#include "GraphsRepresentation.inl"

#endif //GRAPH_LIB_GRAPHSREPRESENTATION_H
