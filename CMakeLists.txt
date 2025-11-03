cmake_minimum_required(VERSION 3.12)
project(GraphCycleCheck CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_cycle
    test_is_simple_cycle.cpp
)

# headers live next to sources
target_include_directories(test_cycle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# --- Kevin Bacon demo ---
add_executable(kevin_bacon
    test_kevin_bacon.cpp
)
target_include_directories(kevin_bacon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
