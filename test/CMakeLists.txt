include_directories(${CMAKE_SOURCE_DIR}/src/inc ${CATCH_INCLUDE_DIR})

add_executable(sudokuTest allTest.cpp bitUtilsTest.cpp boardDataTest.cpp
    boardTest.cpp testData.cpp testUtils.cpp)

target_link_libraries(sudokuTest sudokuLib Catch)
