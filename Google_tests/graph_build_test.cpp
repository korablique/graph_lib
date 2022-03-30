#include "gtest/gtest.h"
#include "../include/Graph.h"

TEST(BuildGraph, EmptyNodesAndNonEmptyEdges) {
    bool exception_caught = false;
    std::vector<std::string> nodes;
    std::vector<std::pair<size_t, size_t>> edges({{0, 1}});
    edges.push_back({0, 1});
    try {
        Graph<std::string>::buildGraph(nodes, edges);
    } catch(...) {
        exception_caught = true;
    }
    EXPECT_TRUE(exception_caught);
}

TEST(BuildGraph, NonEmptyNodesAndEmptyAdjMatrix) {
    bool exception_caught = false;
    std::vector<std::string> nodes({"data"});
    std::vector<std::vector<bool>> adjacency_matrix;
    try {
        Graph<std::string>::buildGraph(nodes, adjacency_matrix);
    } catch(...) {
        exception_caught = true;
    }
    EXPECT_TRUE(exception_caught);
}

TEST(BuildGraph, EmptyNodesAndNonEmptyAdjMatrix) {
    bool exception_caught = false;
    std::vector<std::string> nodes;
    std::vector<std::vector<bool>> adjacency_matrix;
    adjacency_matrix.push_back(std::vector<bool>({0, 1}));
    adjacency_matrix.push_back(std::vector<bool>({1, 0}));
    try {
        Graph<std::string>::buildGraph(nodes, adjacency_matrix);
    } catch(...) {
        exception_caught = true;
    }
    EXPECT_TRUE(exception_caught);
}

TEST(BuildGraph, AdjMatrixIsNotSquare) {
    bool exception_caught = false;
    std::vector<std::string> nodes({"one", "two"});
    std::vector<std::vector<bool>> adjacency_matrix;
    adjacency_matrix.push_back(std::vector<bool>({0, 1, 0}));
    adjacency_matrix.push_back(std::vector<bool>({1, 0, 0}));
    try {
        Graph<std::string>::buildGraph(nodes, adjacency_matrix);
    } catch(...) {
        exception_caught = true;
    }
    EXPECT_TRUE(exception_caught);
}

TEST(BuildGraph, AdjMatrixSizeDoesNotFitNodesNumber) {
    bool exception_caught = false;
    std::vector<std::string> nodes({"one", "two", "three"});
    std::vector<std::vector<bool>> adjacency_matrix;
    adjacency_matrix.push_back(std::vector<bool>({0, 1}));
    adjacency_matrix.push_back(std::vector<bool>({1, 0}));
    try {
        Graph<std::string>::buildGraph(nodes, adjacency_matrix);
    } catch(...) {
        exception_caught = true;
    }
    EXPECT_TRUE(exception_caught);
}

TEST(BuildGraph, AdjMatrixIsNotSymmetric) {
    bool exception_caught = false;
    std::vector<std::string> nodes({"one", "two", "three"});
    std::vector<std::vector<bool>> adjacency_matrix;
    adjacency_matrix.push_back(std::vector<bool>({0, 0, 1}));
    adjacency_matrix.push_back(std::vector<bool>({1, 0, 0}));
    adjacency_matrix.push_back(std::vector<bool>({1, 1, 0}));
    try {
        Graph<std::string>::buildGraph(nodes, adjacency_matrix);
    } catch(...) {
        exception_caught = true;
    }
    EXPECT_TRUE(exception_caught);
}

TEST(BuildGraph, AdjMatrixDiagonalContainsNonZeroElements) {
    bool exception_caught = false;
    std::vector<std::string> nodes({"one", "two", "three"});
    std::vector<std::vector<bool>> adjacency_matrix;
    adjacency_matrix.push_back(std::vector<bool>({0, 1, 1}));
    adjacency_matrix.push_back(std::vector<bool>({1, 1, 1}));
    adjacency_matrix.push_back(std::vector<bool>({1, 1, 0}));
    try {
        Graph<std::string>::buildGraph(nodes, adjacency_matrix);
    } catch(...) {
        exception_caught = true;
    }
    EXPECT_TRUE(exception_caught);
}

TEST(BuildCn, BuildCnWorks) {
    std::vector<std::string> nodes({"one", "two", "three"});
    Graph<std::string> cycle = Graph<std::string>::buildCn(nodes);
    std::vector<std::pair<size_t, size_t>> edges_expected({{0, 1}, {1, 2}, {2, 0}});
    EXPECT_EQ(cycle.getEdgesList(), edges_expected);
}