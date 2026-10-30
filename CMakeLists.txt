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

add_executable(ring_buffer
    ring_buffer/main.cpp
)
target_include_directories(ring_buffer PRIVATE ring_buffer)

# 2. Studies
add_executable(memory_layout
    memory_layout/main.cpp
)
target_include_directories(memory_layout PRIVATE memory_layout)

# Tracy — frame/zone profiler client. Exports Tracy::TracyClient, which carries
# its include path and the TRACY_ENABLE define.
#
# The tag must match the viewer (tracy-profiler.exe) version exactly, or the
# viewer refuses the connection. With TRACY_ENABLE OFF every Tracy macro
# compiles to nothing, so instrumentation can stay in the code.
include(cmake/CPM.cmake)
CPMAddPackage(
    NAME tracy
    GITHUB_REPOSITORY wolfpld/tracy
    GIT_TAG v0.14.1
    OPTIONS "TRACY_ENABLE ON"
)
target_link_libraries(memory_layout PRIVATE Tracy::TracyClient)

add_executable(raii
    raii/main.cpp
)
target_include_directories(raii PRIVATE raii)

# doctest — single-header test framework. Only the header is used, so the
# package is downloaded without running its own CMakeLists.
CPMAddPackage(
    NAME doctest
    GITHUB_REPOSITORY doctest/doctest
    GIT_TAG v2.4.11
    DOWNLOAD_ONLY YES
)
add_executable(raii_test
    raii/vector_test.cpp
)
target_include_directories(raii_test PRIVATE raii ${doctest_SOURCE_DIR})

# Rule of 0 version: separate target, so it can be red while raii_test stays green.
add_executable(raii_imp_test
    raii/imp_vector_test.cpp
)
target_include_directories(raii_imp_test PRIVATE raii ${doctest_SOURCE_DIR})

# 3. Project Euler — one executable per problem, named pe_<n>.
#    CONFIGURE_DEPENDS re-runs the glob when a new problem file is added.
file(GLOB PE_SOURCES CONFIGURE_DEPENDS pe/*.cpp)
foreach(SRC ${PE_SOURCES})
    get_filename_component(NAME ${SRC} NAME_WE)
    add_executable(pe_${NAME} ${SRC})
endforeach()
