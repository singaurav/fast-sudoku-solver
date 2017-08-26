cmake_minimum_required(VERSION 2.8.8)

project(fast_sudoku_solver)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall -O3 -std=gnu++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++11")
endif()

add_subdirectory(src)
add_subdirectory(test)

set(EXT_PROJECTS_DIR ${CMAKE_SOURCE_DIR}/external)

set(CATCH_INCLUDE_DIR ${EXT_PROJECTS_DIR}/catch)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

enable_testing(true)
