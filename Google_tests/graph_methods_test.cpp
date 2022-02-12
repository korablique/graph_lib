#include "gtest/gtest.h"
#include "../GraphsMethods.h"

TEST(GetDegreeListTest, WorksForSimpleGraphs) {
    size_t matrix_size = 4;
    std::vector<std::vector<bool>> adjacency_matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = std::vector<bool>(matrix_size, false);
    }
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][2] = true;
    adjacency_matrix[1][0] = true;
    adjacency_matrix[2][0] = true;
    auto degree_list = getDegreeList(adjacency_matrix);
    std::vector<size_t> expected({2, 1, 1, 0});
    EXPECT_EQ(degree_list, expected);
}

TEST(GetDegreeListTest, WorksForWeightedSimpleGraphs) {
    size_t matrix_size = 4;
    double inf = std::numeric_limits<double>::max();
    std::vector<std::vector<double>> adjacency_matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = std::vector<double>(matrix_size, inf);
    }
    adjacency_matrix[0][0] = 0;
    adjacency_matrix[1][1] = 0;
    adjacency_matrix[2][2] = 0;
    adjacency_matrix[3][3] = 4;
    adjacency_matrix[0][1] = 4;
    adjacency_matrix[0][2] = 3;
    adjacency_matrix[1][0] = 4;
    adjacency_matrix[2][0] = 3;

    auto degree_list = getDegreeList(adjacency_matrix);
    std::vector<size_t> expected({2, 1, 1, 0});
    EXPECT_EQ(degree_list, expected);
}

TEST(GetAdjacencyListTest, WorksForSimpleGraphs) {
    // create adjacency matrix
    size_t matrix_size = 4;
    std::vector<std::vector<bool>> adjacency_matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = std::vector<bool>(matrix_size, false);
    }
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][2] = true;
    adjacency_matrix[1][0] = true;
    adjacency_matrix[2][0] = true;

    // TODO for the first time there is int instead of Node
    std::vector<std::vector<int>> expected(matrix_size);
    expected[0] = std::vector<int>({1, 2});
    expected[1] = std::vector<int>({0});
    expected[2] = std::vector<int>({0});
    expected[3] = std::vector<int>();

    auto adj_list = getAdjacencyList(adjacency_matrix);

    for (int i = 0; i < matrix_size; i++) {
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
    for (int i = 0; i < matrix_size; i++) {
        EXPECT_EQ(adj_list[i], expected[i]);
    }
}

TEST(IsConnectedTest, WorksForDisconnectedGraph) {
    size_t matrix_size = 4;
    std::vector<std::vector<bool>> adjacency_matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = std::vector<bool>(matrix_size, false);
    }
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][2] = true;
    adjacency_matrix[1][0] = true;
    adjacency_matrix[2][0] = true;

    bool is_connected = isConnected(adjacency_matrix);
    EXPECT_FALSE(is_connected);
}

TEST(IsConnectedTest, WorksForConnectedGraph) {
    size_t matrix_size = 4;
    std::vector<std::vector<bool>> adjacency_matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = std::vector<bool>(matrix_size, false);
    }
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][2] = true;
    adjacency_matrix[1][0] = true;
    adjacency_matrix[2][0] = true;
    adjacency_matrix[2][3] = true;
    adjacency_matrix[3][2] = true;

    bool is_connected = isConnected(adjacency_matrix);
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
