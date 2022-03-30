#include <vector>
#include <utility>
#include <unordered_set>
#include "GraphAlgorithms.h"

template<class T1>
Node<T1>::Node(int64_t id, T1 data): m_id(id), m_data(data) {}

template<class T1>
bool Node<T1>::operator==(const Node<T1> &other) const {
    return m_id == other.m_id;
}

template<class T1>
int64_t Node<T1>::getId() const {
    return m_id;
}

template<class T1>
T1 Node<T1>::getData() const {
    return m_data;
}

/**
 * Private constructor for example to create a complement graph (with the same nodes, but different edges).
 * Needed to avoid recreating vertices.
 */
template<typename T>
Graph<T>::Graph(const std::vector<Node<T>> nodes, const std::vector<std::vector<bool>> adjacency_matrix):
        m_nodes(nodes), m_adjacency_matrix(adjacency_matrix) {
    setEdgesList(adjacency_matrix);
}

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
void Graph<T>::setAdjacencyMatrix(std::vector<Node<T>> &nodes, std::vector<std::pair<size_t, size_t>> &edges) {
    m_adjacency_matrix.resize(nodes.size());
    for (auto& line: m_adjacency_matrix) {
        line.resize(nodes.size());
        std::fill(line.begin(), line.end(), false); // clear the matrix
    }
    for (auto& edge: edges) {
        m_adjacency_matrix[edge.first][edge.second] = true;
        m_adjacency_matrix[edge.second][edge.first] = true;
    }
}

template <typename T>
void Graph<T>::setEdgesList(const std::vector<std::vector<bool>> &adjacency_matrix) {
    for (int i = 0; i < adjacency_matrix.size(); ++i) {
        for (int j = i + 1; j < adjacency_matrix.size(); ++j) {
            if (adjacency_matrix[i][j]) {
                std::pair<size_t, size_t> added_pair{i, j};
                m_edges.push_back(added_pair);
            }
        }
    }
}

template<typename T>
void Graph<T>::setNodesList(const std::vector<T> &nodes_data) {
    std::vector<Node<T>> nodes_list;
    for (auto& data : nodes_data) {
        Node<T> node(++m_last_id, data);
        nodes_list.push_back(node);
    }
    m_nodes = nodes_list;
}

template<typename T>
Graph<T>::Graph(const std::vector<T> &nodes_data, const std::vector<std::pair<size_t, size_t>> &edges_list) {
    // create nodes with given data
    setNodesList(nodes_data);
    // copy edges list
    m_edges = edges_list;
    setAdjacencyMatrix(m_nodes, m_edges);
}

template <typename T>
Graph<T>::Graph(const std::vector<T> &nodes_data, const std::vector<std::vector<bool>> &adjacency_matrix) {
    m_adjacency_matrix = adjacency_matrix;
    setEdgesList(adjacency_matrix);
    setNodesList(nodes_data);
}

template<typename T>
std::vector<std::vector<Node<T>>> Graph<T>::getConnectedComponentsImpl(
        const std::vector<std::vector<size_t>>& adjacency_list,
        std::map<size_t, bool>& visited) const {
    std::vector<std::vector<Node<T>>> components;

    std::vector<size_t> remaining_nodes_indices(m_nodes.size());
    // fills the range [first, last) with sequentially increasing values, starting with value
    std::iota(remaining_nodes_indices.begin(), remaining_nodes_indices.end(), 0);

    std::vector<size_t> current_component;
    while (!remaining_nodes_indices.empty()) {
        dfsForConnectedComponentsImpl(remaining_nodes_indices[0], visited, adjacency_list, current_component);
        // convert indices to vertices before adding to vector
        std::vector<Node<T>> current_component_nodes;
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

/**
 * @return degree list in descending order
 */
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
    if (m_nodes.empty()) {
        return false; // graph with no vertices is considered disconnected
    }
    auto adjacency_list = getAdjacencyList();
    size_t vertices_reached = dfs(adjacency_list);
    return vertices_reached == m_adjacency_matrix.size();
}

template<typename T>
std::vector<std::vector<Node<T>>> Graph<T>::getConnectedComponents() const {
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
std::vector<Node<T>> Graph<T>::getNodesList() const {
    return m_nodes;
}

template<typename T>
std::vector<std::pair<size_t, size_t>> Graph<T>::getEdgesList() const {
    return m_edges;
}

/**
 * @return id of the added node
 */
template<typename T>
int64_t Graph<T>::addNode(const T& node_data) {
    Node<T> new_node(++m_last_id, node_data);
    m_nodes.push_back(new_node);
    // change adjacency matrix
    m_adjacency_matrix.push_back(std::vector<bool>(m_nodes.size() - 1, false)); // add new line for new node
    for (auto& line : m_adjacency_matrix) {
        line.resize(line.size() + 1, false); // add new column, initialize new column with false
    }
    return m_last_id;
}

template<typename T>
void Graph<T>::removeNode(int64_t id) {
    // remove node from nodes list
    size_t node_index_to_remove = -1;
    for (int i = 0; i < m_nodes.size(); i++) {
        if (m_nodes[i].m_id == id) {
            m_nodes.erase(m_nodes.begin() + i);
            node_index_to_remove = i;
            break;
        }
    }

    if (node_index_to_remove == -1) {
        // node with this id is not found
        return;
    }

    // change edges list
    auto it = m_edges.begin();
    while(it != m_edges.end()) {
        if((*it).first == node_index_to_remove || (*it).second == node_index_to_remove) {
            it = m_edges.erase(it);
        } else {
            it++;
        }
    }

    // recalculate adjacency matrix
    setAdjacencyMatrix(m_nodes, m_edges);
}

template<class T>
Graph<T> Graph<T>::buildGraph(const std::vector<T> &nodes_data, const std::vector<std::pair<size_t, size_t>> &edges_list) {
    for (auto& edge : edges_list) {
        if (edge.first >= nodes_data.size() || edge.second >= nodes_data.size()) {
            throw std::logic_error("Node index is out of range");
        }
    }
    return Graph<T>(nodes_data, edges_list);
}

template<class T>
Graph<T> Graph<T>::buildGraph(const std::vector<T> &nodes_data, const std::vector<std::vector<bool>> &adjacency_matrix) {
    if (nodes_data.empty() && !adjacency_matrix.empty()) {
        throw std::logic_error("Nodes list is empty while adjacency matrix is not");
    }
    if (!nodes_data.empty() && adjacency_matrix.empty()) {
        throw std::logic_error("Adjacency matrix is empty while nodes list is not");
    }

    if (!adjacency_matrix.empty()) {
        bool is_square = adjacency_matrix.size() == adjacency_matrix[0].size();
        if (!is_square) {
            throw std::logic_error("Matrix is not square");
        }
    }

    bool matrix_size_fits_nodes_number = nodes_data.size() == adjacency_matrix.size();
    if (!matrix_size_fits_nodes_number) {
        throw std::logic_error("Matrix does size does not fit nodes number");
    }

    for (int i = 0; i < adjacency_matrix.size(); i++) {
        for (int j = i + 1; j < adjacency_matrix.size(); j++) {
            if (adjacency_matrix[i][j] != adjacency_matrix[j][i]) {
                throw std::logic_error("Matrix is not symmetric");
            }
        }
    }

    for (int i = 0; i < adjacency_matrix.size(); i++) {
        if (adjacency_matrix[i][i] != 0) {
            throw std::logic_error("Matrix diagonal contains non-zero elements");
        }
    }

    return Graph<T>(nodes_data, adjacency_matrix);
}

template<class T>
bool Graph<T>::operator==(const Graph<T> &other) const {
    // compare data in the nodes
    std::unordered_set<T> nodes_data;
    for (const auto& node : m_nodes) {
        nodes_data.insert(node.m_data);
    }
    std::unordered_set<T> other_nodes_data;
    for (const auto& node : other.getNodesList()) {
        other_nodes_data.insert(node.m_data);
    }
    if (nodes_data != other_nodes_data) {
        return false;
    }

    // compare edges list
    auto other_nodes = other.getNodesList();
    auto other_edges = other.getEdgesList();
    if (m_edges.size() != other_edges.size()) {
        return false;
    }

    for (auto& edge : m_edges) {
        bool edge_found = false;
        for (auto& other_edge : other_edges) {
            // check whether the data at the vertices that form an edge in this graph
            // match the data at the vertices that form an edge of another graph
            if ((m_nodes[edge.first].m_data == other_nodes[other_edge.first].m_data
                        || m_nodes[edge.first].m_data == other_nodes[other_edge.second].m_data)
                    && (m_nodes[edge.second].m_data == other_nodes[other_edge.first].m_data
                        || m_nodes[edge.second].m_data == other_nodes[other_edge.second].m_data)) {
                edge_found = true;
                break;
            }
        }
        if (!edge_found) {
            return false;
        }
    }
    return true;
}

template<typename T>
void Graph<T>::addEdge(int64_t idFirst, int64_t idSecond) {
    bool has_edge = false;
    auto it = m_edges.begin();
    while (it != m_edges.end()) {
        if ((*it).first == idFirst && (*it).second == idSecond || (*it).first == idSecond && (*it).second == idFirst) {
            has_edge = true;
        } else {
            it++;
        }
    }

    if (!has_edge) {
        // find indices of the nodes by their ids
        int index1 = -1, index2 = -1;
        for (int i = 0; i < m_nodes.size(); i++) {
            if (m_nodes[i].getId() == idFirst) {
                index1 = i;
            } else if (m_nodes[i].getId() == idSecond) {
                index2 = i;
            }
        }
        if (index1 == -1 || index2 == -1) {
            // there are no nodes with the given ids
            return;
        }

        m_edges.push_back(std::make_pair(index1, index2));
        setAdjacencyMatrix(m_nodes, m_edges);
    }
}

template<typename T>
void Graph<T>::removeEdge(int64_t idFirst, int64_t idSecond)
{
    auto it = m_edges.begin();
    while (it != m_edges.end()) {
        if ((*it).first == idFirst && (*it).second == idSecond || (*it).first == idSecond && (*it).second == idFirst) {
            it = m_edges.erase(it);
            break;
        } else {
            it++;
        }
    }

    // recalculate adjacency matrix
    setAdjacencyMatrix(m_nodes, m_edges);
}


template<typename T>
bool Graph<T>::hasNode(int64_t id)
{
    size_t has_node_index = -1;
    for (int i = 0; i < m_nodes.size(); i++) {
        if (m_nodes[i].m_id == id) {
            return true;
        }
    }

    if (has_node_index == -1) {
        return false;
    }
}

template<typename T>
bool Graph<T>::hasEdge(int64_t idFirst, int64_t idSecond)
{
    auto it = m_edges.begin();
    bool has_edge = false;
    while(it != m_edges.end()) {
        if((*it).first == idFirst && (*it).second == idSecond || (*it).first == idSecond && (*it).second == idFirst) {
            has_edge = true;
            break;
        } else {
            it++;
        }
    }
    if(has_edge == false){
        return false;
    }
    else{
        return true;
    }
}

template<typename T>
bool Graph<T>::Is_Euleran_Path(){ // проверка на эйлеров путь
    std::vector<size_t> degree_list = getDegreeList();
    auto connected_component = getConnectedComponents();
    int Odd_Vertix = 0; //счетчик нечетных вершин
    int Complicated_Graph_Connected_Component = 0; // счетчик сложных компонент связности
    for (int i = 0; i < degree_list.size(); i++) {
        if ((degree_list[i] % 2) != 0) {
            Odd_Vertix++;
        }
        if (Odd_Vertix > 2) {
            return false;
        }
    }

    if(Odd_Vertix == 1){
        return false;
    }

    for (int i = 0; i < connected_component.size(); i++) {
        if (connected_component[i].size() > 1) {
            Complicated_Graph_Connected_Component++;
        }
    }
    if (Complicated_Graph_Connected_Component >= 2) {
        return false;
    }
    return true;
}

template <typename T>
bool Graph<T>::Is_Euleran_Cycle() { //проверка на Эйлеров цикл
    std::vector<size_t> degree_list = getDegreeList();
    bool is_euleran = Is_Euleran_Path();
    if (is_euleran == 0) {
        return false;
    }
    for (int i = 0; i < degree_list.size(); i++) {
        if ((degree_list[i] % 2) != 0) {
            return false;
        }
    }
    return true;
}

template<typename T>
std::vector<int> Graph<T>::Search_Euleran_Graph() {
    std::vector<int> answer;
    answer.resize(0);
    if(Is_Euleran_Path() == false){
        return answer;
    }
    auto connected_components = getConnectedComponents();
    int Start_Vertix = 0;
    std::vector<size_t> degree_list = getDegreeList();
    std::stack<int> Search_Path;
    int current_Vertix = 0;
    for (int i = 0; i < connected_components.size(); i++) { // поиск стартовой вершины
        if (connected_components[i].size() > 1) {
            for (int j = 0; j < connected_components[i].size(); j++) {
                Node<T> Vert = connected_components[i][j];
                if (degree_list[Vert.m_id] % 2 == 1) { //
                    Start_Vertix = connected_components[i][j];
                    break;
                }
            }
        }
    }

    Search_Path.push(Start_Vertix);
    bool found = false;
    while (Search_Path.empty() == 0) {
        found = false;
        current_Vertix = Search_Path.top();
        for (int i = 0; i < m_adjacency_matrix[current_Vertix].size(); i++) {
            if (m_adjacency_matrix[current_Vertix][i] == 1) {
                found = true; // нашли ребро
                Search_Path.push(i);
                m_adjacency_matrix[current_Vertix][i] = 0; // по сути обрубаем ребро
                m_adjacency_matrix[i][current_Vertix] = 0;
                break;
            }
        }
        if (found == false) {
            answer.push_back(Search_Path.top()); // выводим итоговый ответ
            Search_Path.pop();
        }
    }
    return answer;
}

template <typename T>
bool Graph<T>::Is_Bipartied() {
    std::vector<std::vector<int>> connected_component = getConnectedComponents();
    std::stack<int> Search_Path;
    int current_Vertix = 0;
    if (connected_component.size() != 1)
        return false;
    Search_Path.push(0);
    std::vector<int> painted; // покрашены 1 - зеленый, 2 - желтый
    painted.resize(m_adjacency_matrix[0].size());
    std::vector<int> answer;
    painted[0] = 1;
    Search_Path.push(0);
    bool found;
    while (Search_Path.empty() == 0) {
        found = false; // нашли вершинку
        current_Vertix = Search_Path.top();
        for (int i = 0; i < m_adjacency_matrix[current_Vertix].size(); i++) {
            if (m_adjacency_matrix[current_Vertix][i] == 1) {
                if (painted[i] == 0) {
                    found = true; // нашли
                    Search_Path.push(i);
                    if (painted[current_Vertix] == 2) {
                        painted[i] = 1; // красим в противоположный
                    } else {
                        painted[i] = 2;
                    } // красим в противоположный
                    break;
                } else {
                    if ((painted[current_Vertix] != painted[i])) { // проверка на соответствие двудольности
                        found = false;
                        continue;
                    } else {
                        return false;
                    }
                }
            }
        }
        if (found == false) {
            answer.push_back(Search_Path.top()); // выводим итоговый ответ
            Search_Path.pop();
        }
    }
    return true;
}
