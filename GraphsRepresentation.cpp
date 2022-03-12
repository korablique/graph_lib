#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
#include "GraphsRepresentation.h"

template <typename T>
Graph<T>* Graph<T>::buildCn(const std::vector<Node<T>> &nodes, size_t n){
    std::vector<std::pair<Node<T>, Node<T>>> edges_list;
    for (int i = 0; i < n-2; ++i){
        edges_list.push_back(std::make_pair(nodes[i], nodes[i+1]));
    }
    edges_list.push_back(nodes[n-1], nodes[n]);
    Graph<T> result = Graph(&nodes, &edges_list);
    return &result;
}

template <typename T>
void Graph<T>::setAdjacencyMatrix(std::vector<Node<T>> &nodes, std::vector<std::pair<Node<T>, Node<T>>> &edges){
    m_adjacency_matrix.resize(nodes.size());
    for (auto i: m_adjacency_matrix){
        i.resize(nodes.size());
    }
    for (auto i: edges){
        m_adjacency_matrix[i.first][i.second] = true;
        m_adjacency_matrix[i.second][i.first] = true;

    }
}

template <typename T>
Graph<T>::Graph(std::vector<Node<T>> &nodes_list, std::vector<std::pair<Node<T>, Node<T>>> &edges_list){
    m_nodes = nodes_list;
    m_edges = edges_list;
    makeAdjacencyMatrix(nodes_list, edges_list);
}

template <typename T>
Graph<T>::Graph(std::vector<Node<T>> &nodes, std::vector<std::vector<bool>> &adjacency_matrix){
    for (const auto& i: adjacency_matrix){
        m_adjacency_matrix.push_back(i);
    }
    for (int i = 0; i < adjacency_matrix.size(); ++i){ // making vector of edges
        for (int j = 0; j < adjacency_matrix.size(); ++j){
            if (j == i + 1){
                i++;
                j = -1;
                continue;
            }
            if (adjacency_matrix[i][j]) {
                std::pair<Node<T>, Node<T>> added_pair{nodes[i], nodes[j]};
                m_edges.push_back(added_pair);
            }
        }
    }
    m_nodes = nodes;
}

template <typename T>
void Graph<T>::AddNode(Node<T> node)
{
    m_nodes.pop_back(node);
    for (auto & i : m_adjacency_matrix)
    {
        i.push_back(false);
    }
    std::vector<bool> adjacency_matrix_add;
    adjacency_matrix_add.reserve(m_adjacency_matrix.size() + 1);
    for (auto && i : adjacency_matrix_add)
    {
        i = false;
    }
    m_adjacency_matrix.push_back(adjacency_matrix_add);
}

template <typename T>
void Graph<T>::RemoveNode(Node<T> node)
{
}

template <typename T>
void Graph<T>::AddEdge(Node<T> nodeFirst, Node<T> nodeSecond)
{
}