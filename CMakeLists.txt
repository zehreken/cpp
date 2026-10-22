cmake_minimum_required(VERSION 3.20)
project(Cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Each folder is a standalone study program; headers sit next to their sources,
# so the folder itself is the include root.

# 1. Data structures
add_executable(linked_list
    linked_list/main.cpp
    linked_list/linked_list.cpp
    linked_list/d_linked_list.cpp
)
target_include_directories(linked_list PRIVATE linked_list)

add_executable(graph
    graph/main.cpp
    graph/graph.cpp
)
target_include_directories(graph PRIVATE graph)

# 2. Project Euler — one executable per problem, named pe_<n>.
#    CONFIGURE_DEPENDS re-runs the glob when a new problem file is added.
file(GLOB PE_SOURCES CONFIGURE_DEPENDS pe/*.cpp)
foreach(SRC ${PE_SOURCES})
    get_filename_component(NAME ${SRC} NAME_WE)
    add_executable(pe_${NAME} ${SRC})
endforeach()
