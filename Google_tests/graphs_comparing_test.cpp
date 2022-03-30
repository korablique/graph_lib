#include "gtest/gtest.h"
#include "../GraphsRepresentation.h"

TEST(GraphsComparing, CompareEqualGraphs) {
    std::vector<std::string> nodes_data({"one", "two"});
    std::vector<std::vector<bool>> adj_matrix({{0, 1}, {1, 0}});
    auto g1 = Graph<std::string>::buildGraph(nodes_data, adj_matrix);
    auto g2 = Graph<std::string>::buildGraph(nodes_data, adj_matrix);
    EXPECT_TRUE(g1 == g2);
}

TEST(GraphsComparing, CompareEqualGraphsWithDifferentNodesOrder) {
    std::vector<std::string> nodes_data1({"one", "two", "three", "four"});
    std::vector<std::vector<bool>> adj_matrix1;
    adj_matrix1.push_back({0, 1, 0, 0});
    adj_matrix1.push_back({1, 0, 0, 1});
    adj_matrix1.push_back({0, 0, 0, 1});
    adj_matrix1.push_back({0, 1, 1, 0});

    std::vector<std::string> nodes_data2({"two", "four", "three", "one"});
    std::vector<std::vector<bool>> adj_matrix2;
    adj_matrix2.push_back({0, 1, 0, 1});
    adj_matrix2.push_back({1, 0, 1, 0});
    adj_matrix2.push_back({0, 1, 0, 0});
    adj_matrix2.push_back({1, 0, 0, 0});

    auto g1 = Graph<std::string>::buildGraph(nodes_data1, adj_matrix1);
    auto g2 = Graph<std::string>::buildGraph(nodes_data2, adj_matrix2);
    EXPECT_TRUE(g1 == g2);
}

TEST(GraphsComparing, CompareEqualGraphsWithDifferentEdgesOrder) {
    std::vector<std::string> nodes_data({"one", "two", "three"});
    std::vector<std::pair<size_t, size_t>> edges1({{0, 1}, {1, 2}});
    std::vector<std::pair<size_t, size_t>> edges2({{2, 1}, {0, 1}});

    auto g1 = Graph<std::string>::buildGraph(nodes_data, edges1);
    auto g2 = Graph<std::string>::buildGraph(nodes_data, edges2);
    EXPECT_TRUE(g1 == g2);
}

TEST(GraphsComparing, CompareGraphsWithoutNodes) {
    std::vector<std::string> nodes_data;
    std::vector<std::pair<size_t, size_t>> edges;
    auto g1 = Graph<std::string>::buildGraph(nodes_data, edges);
    auto g2 = Graph<std::string>::buildGraph(nodes_data, edges);
    EXPECT_TRUE(g1 == g2);
}
