cmake_minimum_required(VERSION 3.20)
project(graph_lib)

set(CMAKE_CXX_STANDARD 17)

add_executable(graph_lib main.cpp
        GraphsMethods.cpp GraphsMethods.h)

add_subdirectory(Google_tests)

