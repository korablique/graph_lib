#include "gtest/gtest.h"
#include "../GraphsMethods.h"

class GraphMethodsTest : public ::testing::Test {
protected:
    // for disconnected simple graph
    std::vector<std::vector<bool>> adj_matrix_disconnected_simple;
    // for connected simple graph
    std::vector<std::vector<bool>> adj_matrix_connected_simple;
    // for connected weighted simple graph
    std::vector<std::vector<double>> adj_matrix_connected_weighted_simple;

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
    }
};


TEST_F(GraphMethodsTest, GetDegreeListWorksForSimpleGraphs) {
    auto degree_list = getDegreeList(adj_matrix_disconnected_simple);
    std::vector<size_t> expected({2, 1, 1, 0});
    EXPECT_EQ(degree_list, expected);
}

TEST_F(GraphMethodsTest, GetDegreeListWorksForWeightedSimpleGraphs) {
    auto degree_list = getDegreeList(adj_matrix_connected_weighted_simple);
    std::vector<size_t> expected({2, 1, 1, 0});
    EXPECT_EQ(degree_list, expected);
}

TEST_F(GraphMethodsTest, GetAdjacencyListWorksForSimpleGraphs) {
    // TODO for the first time there is int instead of Node
    std::vector<std::vector<int>> expected;
    expected.push_back(std::vector<int>({1, 2}));
    expected.push_back(std::vector<int>({0}));
    expected.push_back(std::vector<int>({0}));
    expected.push_back(std::vector<int>());

    auto adj_list = getAdjacencyList(adj_matrix_disconnected_simple);

    EXPECT_EQ(adj_list.size(), expected.size());
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_EQ(adj_list[i], expected[i]);
    }
}

TEST(GetAdjacencyListTest, WorksForDirectedGraphs) {
    // create adjacency matrix
    size_t matrix_size = 4;
    std::vector<std::vector<bool>> adjacency_matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = std::vector<bool>(matrix_size, false);
    }
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][2] = true;

    // TODO for the first time there is int instead of Node
    std::vector<std::vector<int>> expected(matrix_size);
    expected[0] = std::vector<int>({1, 2});

    auto adj_list = getAdjacencyList(adjacency_matrix);

    EXPECT_EQ(adj_list.size(), expected.size());
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_EQ(adj_list[i], expected[i]);
    }
}

TEST_F(GraphMethodsTest, IsConnectedWorksForDisconnectedGraph) {
    bool is_connected = isConnected(adj_matrix_disconnected_simple);
    EXPECT_FALSE(is_connected);
}

TEST_F(GraphMethodsTest, IsConnectedWorksForConnectedSimpleGraph) {
    bool is_connected = isConnected(adj_matrix_connected_simple);
    EXPECT_TRUE(is_connected);
}

TEST(IsConnectedTest, WorksForDirectedGraph) {
    size_t matrix_size = 4;
    std::vector<std::vector<bool>> adjacency_matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = std::vector<bool>(matrix_size, false);
    }
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][2] = true;
    adjacency_matrix[2][3] = true;

    bool is_connected = isConnected(adjacency_matrix);
    EXPECT_TRUE(is_connected);

    adjacency_matrix[2][3] = false;
    is_connected = isConnected(adjacency_matrix);
    EXPECT_FALSE(is_connected);
}
