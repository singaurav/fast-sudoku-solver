include_directories(${CMAKE_SOURCE_DIR}/src/inc ${CATCH_INCLUDE_DIR})

add_executable(sudokuTest test.cpp)

target_link_libraries(sudokuTest sudokuLib Catch)
