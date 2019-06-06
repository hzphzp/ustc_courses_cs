cmake_minimum_required(VERSION 3.12)
project(lab2)

set(CMAKE_CXX_STANDARD 14)
include_directories(src/includes)
add_executable(lab2 src/main.cpp src/includes/DataStructure.h src/DataStructure/course.cpp src/DataStructure/RedBlackTree.cpp)