cmake_minimum_required(VERSION 3.20)
project(graph_lib VERSION 1.0.1 DESCRIPTION "library for a simple graph")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Google_tests)

add_library(graph_lib
        GraphAlgorithms.cpp)
