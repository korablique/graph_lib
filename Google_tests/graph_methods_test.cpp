#include "gtest/gtest.h"
#include "../GraphsRepresentation.h"

class GraphMethodsTest : public ::testing::Test {
protected:
    // for disconnected simple graph
    std::vector<std::vector<bool>> adj_matrix_disconnected_simple;
    // for connected simple graph
    std::vector<std::vector<bool>> adj_matrix_connected_simple;
    // for connected weighted simple graph
    std::vector<std::vector<double>> adj_matrix_connected_weighted_simple;
    // for disconnected directed graph
    std::vector<std::vector<bool>> adj_matrix_disconnected_directed;

    void SetUp() override {
        // for disconnected simple graph
        size_t matrix_size = 4;
        for (int i = 0; i < matrix_size; i++) {
            adj_matrix_disconnected_simple.push_back(std::vector<bool>(matrix_size, false));
        }
        adj_matrix_disconnected_simple[0][1] = true;
        adj_matrix_disconnected_simple[1][0] = true;
        adj_matrix_disconnected_simple[0][2] = true;
        adj_matrix_disconnected_simple[2][0] = true;

        // for connected simple graph
        adj_matrix_connected_simple = adj_matrix_disconnected_simple;
        adj_matrix_connected_simple[2][3] = true;
        adj_matrix_connected_simple[3][2] = true;

        // for connected weighted simple graph
        double inf = std::numeric_limits<double>::max();
        for (int i = 0; i < matrix_size; i++) {
            adj_matrix_connected_weighted_simple.push_back(std::vector<double>(matrix_size, inf));
        }
        adj_matrix_connected_weighted_simple[0][0] = 0;
        adj_matrix_connected_weighted_simple[1][1] = 0;
        adj_matrix_connected_weighted_simple[2][2] = 0;
        adj_matrix_connected_weighted_simple[3][3] = 4;
        adj_matrix_connected_weighted_simple[0][1] = 4;
        adj_matrix_connected_weighted_simple[0][2] = 3;
        adj_matrix_connected_weighted_simple[1][0] = 4;
        adj_matrix_connected_weighted_simple[2][0] = 3;

        // for disconnected directed graph
        for (int i = 0; i < matrix_size; i++) {
            adj_matrix_disconnected_directed.push_back(std::vector<bool>(matrix_size, false));
        }
        adj_matrix_disconnected_directed[0][1] = true;
        adj_matrix_disconnected_directed[0][2] = true;
    }
};


TEST_F(GraphMethodsTest, GetDegreeListWorksForSimpleGraphs) {
    std::vector<Node<int>> nodes({Node<int>(0), Node<int>(1), Node<int>(2), Node<int>(3)});
    Graph<int> graph(nodes, adj_matrix_disconnected_simple);
    auto degree_list = graph.getDegreeList();
    std::vector<size_t> expected({2, 1, 1, 0});
    EXPECT_EQ(degree_list, expected);
}

// weighted graph has not been implemented yet
//TEST_F(GraphMethodsTest, GetDegreeListWorksForWeightedSimpleGraphs) {
//    auto degree_list = getDegreeList(adj_matrix_connected_weighted_simple);
//    std::vector<size_t> expected({2, 1, 1, 0});
//    EXPECT_EQ(degree_list, expected);
//}

TEST_F(GraphMethodsTest, GetAdjacencyListWorksForSimpleGraphs) {
    std::vector<std::vector<size_t>> expected;
    expected.push_back(std::vector<size_t>({1, 2}));
    expected.push_back(std::vector<size_t>({0}));
    expected.push_back(std::vector<size_t>({0}));
    expected.push_back(std::vector<size_t>());

    std::vector<Node<int>> nodes({Node<int>(0), Node<int>(1), Node<int>(2), Node<int>(3)});
    Graph<int> graph(nodes, adj_matrix_disconnected_simple);
    auto adj_list = graph.getAdjacencyList();

    EXPECT_EQ(adj_list, expected);
}

// directed graph has not been implemented yet
//TEST_F(GraphMethodsTest, GetAdjacencyListWorksForDirectedGraphs) {
//    std::vector<std::vector<size_t>> expected(adj_matrix_disconnected_directed.size());
//    expected[0] = std::vector<size_t>({1, 2});
//
//    auto adj_list = getAdjacencyList(adj_matrix_disconnected_directed);
//
//    EXPECT_EQ(adj_list.size(), expected.size());
//    for (int i = 0; i < expected.size(); i++) {
//        EXPECT_EQ(adj_list[i], expected[i]);
//    }
//}

TEST_F(GraphMethodsTest, IsConnectedWorksForDisconnectedGraph) {
    std::vector<Node<int>> nodes({Node<int>(0), Node<int>(1), Node<int>(2), Node<int>(3)});
    Graph<int> graph(nodes, adj_matrix_disconnected_simple);
    bool is_connected = graph.isConnected();
    EXPECT_FALSE(is_connected);
}

TEST_F(GraphMethodsTest, IsConnectedWorksForConnectedSimpleGraph) {
    std::vector<Node<int>> nodes({Node<int>(0), Node<int>(1), Node<int>(2), Node<int>(3)});
    Graph<int> graph(nodes, adj_matrix_connected_simple);
    bool is_connected = graph.isConnected();
    EXPECT_TRUE(is_connected);
}

// directed graph has not been implemented yet
//TEST(IsConnectedTest, WorksForDirectedGraph) {
//    size_t matrix_size = 4;
//    std::vector<Node<int>> nodes({0, 1, 2, 3});
//    std::vector<std::vector<bool>> adjacency_matrix(matrix_size);
//    for (int i = 0; i < matrix_size; i++) {
//        adjacency_matrix[i] = std::vector<bool>(matrix_size, false);
//    }
//    adjacency_matrix[0][1] = true;
//    adjacency_matrix[0][2] = true;
//    adjacency_matrix[2][3] = true;
//
//    bool is_connected = isConnected(nodes, adjacency_matrix);
//    EXPECT_TRUE(is_connected);
//
//    adjacency_matrix[2][3] = false;
//    is_connected = isConnected(nodes, adjacency_matrix);
//    EXPECT_FALSE(is_connected);
//}

TEST_F(GraphMethodsTest, GetConnectedComponents) {
    std::vector<Node<int>> nodes({Node<int>(0), Node<int>(1), Node<int>(2), Node<int>(3)});
    Graph<int> graph(nodes, adj_matrix_disconnected_simple);
    auto components = graph.getConnectedComponents();
    std::vector<std::vector<Node<int>>> expected;
    expected.push_back({Node<int>(0), Node<int>(1), Node<int>(2)});
    expected.push_back({Node<int>(3)});
    EXPECT_EQ(components, expected);

    // graph with more connected components
    nodes.push_back(Node<int>(4));
    nodes.push_back(Node<int>(5));

    size_t matrix_size = nodes.size();
    std::vector<std::vector<bool>> adj_matrix;
    for (int i = 0; i < matrix_size; i++) {
        adj_matrix.push_back(std::vector<bool>(matrix_size, false));
    }
    adj_matrix[1][2] = true;
    adj_matrix[2][1] = true;
    adj_matrix[3][4] = true;
    adj_matrix[4][3] = true;
    adj_matrix[3][5] = true;
    adj_matrix[5][3] = true;
    adj_matrix[4][5] = true;
    adj_matrix[5][4] = true;
    
    Graph<int> graph2(nodes, adj_matrix);
    auto components2 = graph2.getConnectedComponents();
    expected.clear();
    expected.push_back({Node<int>(0)});
    expected.push_back({Node<int>(1), Node<int>(2)});
    expected.push_back({Node<int>(3), Node<int>(4), Node<int>(5)});
    EXPECT_EQ(components2, expected);
}

TEST(GetConnectedComponents, WorksForIsolatedNodes) {
    std::vector<Node<int>> nodes = {Node<int>(0), Node<int>(1), Node<int>(2)};

    // graph without edges
    size_t matrix_size = nodes.size();
    std::vector<std::vector<bool>> adj_matrix;
    for (int i = 0; i < matrix_size; i++) {
        adj_matrix.push_back(std::vector<bool>(matrix_size, false));
    }
    Graph<int> graph(nodes, adj_matrix);

    std::vector<std::vector<Node<int>>> expected({{Node<int>(0)}, {Node<int>(1)}, {Node<int>(2)}});
    auto components = graph.getConnectedComponents();
    EXPECT_EQ(components, expected);
}

// directed graph has not been implemented yet
//TEST_F(GraphMethodsTest, GetConnectedComponentsWorksForDirectedGraph) {
//    std::vector<Node<int>> nodes = {0, 1, 2, 3};
//    auto components = getConnectedComponents(nodes, adj_matrix_disconnected_directed);
//    std::vector<std::vector<Node<int>>> expected({{0, 1, 2}, {3}});
//    EXPECT_EQ(components, expected);
//}

// 0 1 1 0
// 1 0 0 0
// 1 0 0 0
// 0 0 0 0
TEST_F(GraphMethodsTest, GetComplementGraphTest) {
    std::vector<Node<int>> nodes({Node<int>(0), Node<int>(1), Node<int>(2), Node<int>(3)});
    Graph<int> graph(nodes, adj_matrix_disconnected_simple);
    Graph complement_graph = graph.getComplementGraph();
    std::vector<std::vector<bool>> expected;
    expected.push_back({0, 0, 0, 1});
    expected.push_back({0, 0, 1, 1});
    expected.push_back({0, 1, 0, 1});
    expected.push_back({1, 1, 1, 0});

    EXPECT_EQ(complement_graph.getAdjacencyMatrix(), expected);
}

TEST_F(GraphMethodsTest, AddNode) {
    std::vector<Node<std::string>> nodes(
            {Node<std::string>("0"), Node<std::string>("1"), Node<std::string>("2"), Node<std::string>("3")});
    Graph<std::string> graph(nodes, adj_matrix_disconnected_simple);
    Node<std::string> new_node("new");
    graph.addNode(new_node);

    std::vector<Node<std::string>> nodes_expected = nodes;
    nodes_expected.push_back(new_node);
    EXPECT_EQ(graph.getNodesList(), nodes_expected);

    std::vector<std::vector<bool>> adj_matrix_expected;
    adj_matrix_expected.push_back({0, 1, 1, 0, 0});
    adj_matrix_expected.push_back({1, 0, 0, 0, 0});
    adj_matrix_expected.push_back({1, 0, 0, 0, 0});
    adj_matrix_expected.push_back({0, 0, 0, 0, 0});
    adj_matrix_expected.push_back({0, 0, 0, 0, 0});
    EXPECT_EQ(graph.getAdjacencyMatrix(), adj_matrix_expected);
}
