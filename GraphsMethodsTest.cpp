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
    adjacency_matrix[3][0] = true;
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
    std::cout << "getDegreeListTest passed" << std::endl;
}

void graphMethodsTest() {
    getDegreeListTest();
    getDegreeListForWeightedGraphTest();
}
