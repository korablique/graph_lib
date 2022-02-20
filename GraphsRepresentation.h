#ifndef GRAPH_LIB_GRAPHSREPRESENTATION_H
#define GRAPH_LIB_GRAPHSREPRESENTATION_H

template <class T1>
class Node{
private:
    T1 m_data;
public:
    explicit Node(T1 data): m_data(data){};
};

template <class T2>
class Graph{
private:
    std::vector<Node<T2>> m_nodes;
    std::vector<std::pair<Node<T2>, Node<T2>>> m_edges;
    std::vector<std::vector<bool>> m_adjacency_matrix;

    void makeAdjacencyMatrix(std::vector<Node<T2>> &nodes, std::vector<std::pair<Node<T2>, Node<T2>>> &edges);

public:
    Graph(std::vector<Node<T2>> &nodes_list, std::vector<std::pair<Node<T2>, Node<T2>>> &edges_list);
    explicit Graph(std::vector<Node<T2>> &nodes, std::vector<std::vector<bool>> &adjacency_matrix);

    std::vector<std::vector<bool>> getAdjacencyMatrix(){ return m_adjacency_matrix; }
};

#endif //GRAPH_LIB_GRAPHSREPRESENTATION_H
