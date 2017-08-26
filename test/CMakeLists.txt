include_directories(${CMAKE_SOURCE_DIR}/src/inc ${CATCH_INCLUDE_DIR})

add_executable(sudokuTest allTest.cpp bitUtilsTest.cpp boardDataTest.cpp
    boardTest.cpp testData.cpp testUtils.cpp)

target_link_libraries(sudokuTest sudokuLib Catch)

add_custom_command( TARGET sudokuTest
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E echo "Copying sudoku puzzles.."
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test/data ${CMAKE_BINARY_DIR}
)
