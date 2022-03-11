#include <vector>
#include <utility>
#include "GraphsRepresentation.h"

template <typename T>
Graph<T>* Graph<T>::buildCn(const std::vector<T> &nodes, size_t n) {
    std::vector<std::pair<T, T>> edges_list;
    for (int i = 0; i < n-2; ++i){
        edges_list.push_back(std::make_pair(nodes[i], nodes[i+1]));
    }
    edges_list.push_back(nodes[n-1], nodes[n]);
    Graph<T> result = Graph(&nodes, &edges_list);
    return &result;
}

template <typename T>
void Graph<T>::setAdjacencyMatrix(std::vector<T> &nodes, std::vector<std::pair<T, T>> &edges) {
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
Graph<T>::Graph(const std::vector<T> &nodes_list, const std::vector<std::pair<T, T>> &edges_list) {
    m_nodes = nodes_list;
    m_edges = edges_list;
    makeAdjacencyMatrix(nodes_list, edges_list);
}

template <typename T>
Graph<T>::Graph(const std::vector<T> &nodes, const std::vector<std::vector<bool>> &adjacency_matrix) {
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
                std::pair<T, T> added_pair{nodes[i], nodes[j]};
                m_edges.push_back(added_pair);
            }
        }
    }
    m_nodes = nodes;
}

size_t dfsImpl(
        const size_t node_index,
        std::map<size_t, bool>& visited,
        const std::vector<std::vector<size_t>>& adjacency_list) {
    size_t visited_vertices = 1;
    visited[node_index] = true;
    for (auto& v : adjacency_list[node_index]) {
        if (!visited[v]) {
            visited_vertices += dfsImpl(v, visited, adjacency_list);
        }
    }
    return visited_vertices;
}

size_t dfs(const std::vector<std::vector<size_t>>& adjacency_list) {
    std::map<size_t, bool> visited;
    for (auto index = 0; index < adjacency_list.size(); ++index) {
        visited.insert({index, false});
    }
    return dfsImpl(0, visited, adjacency_list);
}

void dfsForConnectedComponentsImpl(
        size_t node_index,
        std::map<size_t, bool>& visited,
        const std::vector<std::vector<size_t>>& adjacency_list,
        std::vector<size_t>& connected_component) {
    visited[node_index] = true;
    connected_component.push_back(node_index);
    for (auto& v : adjacency_list[node_index]) {
        if (!visited[v]) {
            dfsForConnectedComponentsImpl(v, visited, adjacency_list, connected_component);
        }
    }
}

template<typename T>
std::vector<std::vector<T>> Graph<T>::getConnectedComponentsImpl(
        const std::vector<std::vector<size_t>>& adjacency_list,
        std::map<size_t, bool>& visited) const {
    std::vector<std::vector<T>> components;

    std::vector<size_t> remaining_nodes_indices(m_nodes.size());
    // fills the range [first, last) with sequentially increasing values, starting with value
    std::iota(remaining_nodes_indices.begin(), remaining_nodes_indices.end(), 0);

    std::vector<size_t> current_component;
    while (!remaining_nodes_indices.empty()) {
        dfsForConnectedComponentsImpl(remaining_nodes_indices[0], visited, adjacency_list, current_component);
        // convert indices to vertices before adding to vector
        std::vector<T> current_component_nodes;
        for (auto i : current_component) {
            current_component_nodes.push_back(m_nodes[i]);
        }
        components.push_back(current_component_nodes);
        current_component_nodes.clear();

        for (auto item : current_component) {
            // remove() moves the elements to be removed to the end of vector
            // and returns the iterator to the first element to be removed.
            // erase() removes all elements from this iterator to remaining_nodes.end()
            remaining_nodes_indices.erase(std::remove(
                    remaining_nodes_indices.begin(), remaining_nodes_indices.end(), item), remaining_nodes_indices.end());
        }
        current_component.clear();
    }
    return components;
}

template<typename T>
std::vector<size_t> Graph<T>::getDegreeList() const {
    // vertex degree = sum of ones in the matrix row
    auto adjacency_matrix = getAdjacencyMatrix();
    std::vector<size_t> degree_list(adjacency_matrix.size());
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        degree_list[i] = std::count(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), true);
    }
    std::sort(degree_list.rbegin(), degree_list.rend());   // reverse iterators
    return degree_list;
}

/**
 * @param adjacency_matrix
 * @return list of nodes' indices
 */
template<typename T>
std::vector<std::vector<size_t>> Graph<T>::getAdjacencyList() const {
    auto adjacency_matrix = getAdjacencyMatrix();
    std::vector<std::vector<size_t>> adj_list(adjacency_matrix.size());
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        for (int j = 0; j < adjacency_matrix.size(); j++) {
            if (adjacency_matrix[i][j]) {
                adj_list[i].push_back(j);
            }
        }
    }
    return adj_list;
}

template<typename T>
bool Graph<T>::isConnected() const {
    auto adjacency_list = getAdjacencyList();
    size_t vertices_reached = dfs(adjacency_list);
    return vertices_reached == m_adjacency_matrix.size();
}

template<typename T>
std::vector<std::vector<T>> Graph<T>::getConnectedComponents() const {
    auto adjacency_list = getAdjacencyList();
    std::map<size_t, bool> visited;
    for (auto index = 0; index < m_nodes.size(); index++) {
        visited.insert({index, false});
    }
    return getConnectedComponentsImpl(adjacency_list, visited);
}

template<typename T>
Graph<T> Graph<T>::getComplementGraph() const {
    std::vector<std::vector<bool>> complement_adj_matrix(m_adjacency_matrix.size());
    for (auto& line : complement_adj_matrix) {
        line = std::vector<bool>(m_adjacency_matrix.size());
    }

    // invert matrix
    for (size_t i = 0; i < m_adjacency_matrix.size(); i++) {
        for (size_t j = 0; j < m_adjacency_matrix.size(); j++) {
            if (i == j) {
                continue; // there must be zeros on the diagonal
            }
            m_adjacency_matrix[i][j] ? complement_adj_matrix[i][j] = false : complement_adj_matrix[i][j] = true;
        }
    }
    Graph<T> complement_graph(m_nodes, complement_adj_matrix);
    return complement_graph;
}

template<typename T>
std::vector<std::vector<bool>> Graph<T>::getAdjacencyMatrix() const {
    return m_adjacency_matrix;
}

template<typename T>
std::vector<T> Graph<T>::getNodesList() const {
    return m_nodes;
}

template<typename T>
void Graph<T>::addNode(const T& node) {
    m_nodes.push_back(node);
    // change adjacency matrix
    m_adjacency_matrix.push_back(std::vector<bool>(m_nodes.size() - 1, false)); // add new line for new node
    for (auto& line : m_adjacency_matrix) {
        line.resize(line.size() + 1, false); // add new column, initialize new column with false
    }
}
