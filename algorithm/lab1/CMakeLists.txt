cmake_minimum_required(VERSION 3.13)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/include)

add_executable(lab1
        src/data_struction/max_heep.cpp
        src/include/data_struction.h
        src/main.cpp
        CMakeLists.txt src/sort_algorithms/sort_max_heap.cpp src/include/sort_algorithms.h src/result_visual/myprint.cpp src/include/result_visual.h src/sort_algorithms/sort_insert.cpp src/sort_algorithms/sort_quick.cpp src/sort_algorithms/sort_merge.cpp src/data/generate.cpp src/include/data.h src/data/copy.cpp)
