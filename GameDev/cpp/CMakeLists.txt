cmake_minimum_required(VERSION 3.23)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp
        pointer/array.cpp
        pointer/pointer_vs_array.cpp pointer/lottary_practice.cpp pointer/multiple_pointer.cpp pointer/multi_dim_array.cpp)
