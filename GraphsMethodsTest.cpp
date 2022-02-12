#include <vector>
#include <cassert>
#include <iostream>
#include "GraphsMethodsTest.h"
#include "GraphsMethods.h"

void getDegreeListTest() {
    size_t matrix_size = 4;
    std::vector<std::vector<bool>> adjacency_matrix(matrix_size);
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = std::vector<bool>(matrix_size, false);
    }
    adjacency_matrix[0][1] = true;
    adjacency_matrix[0][2] = true;
    adjacency_matrix[1][0] = true;
    adjacency_matrix[2][0] = true;
    std::vector<size_t> degree_list = getDegreeList(adjacency_matrix);
    std::vector<size_t> expected({2, 1, 1, 0});
    assert(degree_list == expected);
    std::cout << "getDegreeListTest passed" << std::endl;
}

void getDegreeListForWeightedGraphTest() {
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

    std::vector<size_t> degree_list = getDegreeList(adjacency_matrix);
    std::vector<size_t> expected({2, 1, 1, 0});
    assert(degree_list == expected);
    std::cout << "getDegreeListForWeightedGraphTest passed" << std::endl;
}

void getAdjacencyListTest() {
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

    std::vector<std::vector<int>> adj_list = getAdjacencyList(adjacency_matrix);

    for (int i = 0; i < matrix_size; i++) {
        if (adj_list[i] != expected[i]) {
            std::cout << "getAdjacencyListTest failed, list " << i << ", actual:" << std::endl;
            for (int element : adj_list[i]) {
                std::cout << element << ' ';
            }
            std::cout << std::endl;

            std::cout << "expected:" << std::endl;
            for (int element : expected[i]) {
                std::cout << element << ' ';
            }
            std::cout << std::endl;
            abort();
        }
    }

    // for directed graph
    adjacency_matrix[1][0] = false;
    adjacency_matrix[2][0] = false;
    expected[1].clear();
    expected[2].clear();
    adj_list = getAdjacencyList(adjacency_matrix);
    for (int i = 0; i < matrix_size; i++) {
        assert(adj_list[i] == expected[i]);
    }

    std::cout << "getAdjacencyListTest passed" << std::endl;
}

void isConnectedTest() {
    // disconnected graph
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
    assert(!is_connected);

    // make this graph connected
    adjacency_matrix[2][3] = true;
    adjacency_matrix[3][2] = true;
    is_connected = isConnected(adjacency_matrix);
    assert(is_connected);

    // directed graph
    adjacency_matrix[3][2] = false;
    adjacency_matrix[1][0] = false;
    adjacency_matrix[2][0] = false;
    is_connected = isConnected(adjacency_matrix);
    assert(is_connected);
    std::cout << "isConnectedTest passed" << std::endl;
}


void graphMethodsTest() {
    getDegreeListTest();
    getDegreeListForWeightedGraphTest();
    getAdjacencyListTest();
    isConnectedTest();
}
