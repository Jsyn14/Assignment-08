cmake_minimum_required(VERSION 3.15)
project(test_cycle_proj CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_cycle
    test_is_simple_cycle.cpp
)

target_include_directories(test_cycle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
