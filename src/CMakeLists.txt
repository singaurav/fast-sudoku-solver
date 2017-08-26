include_directories(inc)

set(SUDOKU_LIB_SRCS board.cpp boardData.cpp io.cpp misc.cpp
    option.cpp)

add_library(sudokuLib STATIC ${SUDOKU_LIB_SRCS})

add_executable(sudoku ${SUDOKU_LIB_SRCS} main.cpp)
