#include <vector>
#include <iostream>
#include <utility>
#include "GraphsRepresentation.h"

template <typename T>
void Graph<T>::makeAdjacencyMatrix(std::vector<Node<T>> &nodes, std::vector<std::pair<Node<T>, Node<T>>> &edges){
m_adjacency_matrix.resize(nodes.size());
for (auto i: m_adjacency_matrix){
i.resize(nodes.size());
}
for (auto i: edges){
m_adjacency_matrix[i.first][i.second] = true;
}
}

template <typename T>
Graph<T>::Graph(std::vector<Node<T>> &nodes_list, std::vector<std::pair<Node<T>, Node<T>>> &edges_list){
    for (auto i: nodes_list){
        m_nodes.push_back(i);
    }
    for (auto i: edges_list){
        m_edges.push_back(i);
    }
    makeAdjacencyMatrix(nodes_list, edges_list);
}

template <typename T>
Graph<T>::Graph(std::vector<Node<T>> &nodes, std::vector<std::vector<bool>> &adjacency_matrix){
    for (int i = 0; i < adjacency_matrix.size(); ++i){ // copying adjacency matrix and making vector of edges
        for (int j = 0; j < adjacency_matrix.size(); ++j){
            m_adjacency_matrix[i][j] = adjacency_matrix[i][j];
        }
    }
    for (int i = 0; i < adjacency_matrix.size(); ++i){ // copying adjacency matrix and making vector of edges
        for (int j = 0; j < adjacency_matrix.size(); ++j){
            if (j == i + 1){
                i++;
                j = -1;
                continue;
            }
            std::pair<Node<T>, Node<T>> added_pair {i, j};
            m_edges.push_back(added_pair);
        }
    }
    for (auto i: nodes){ // copying nodes
        m_nodes.push_back(i);
    }
}