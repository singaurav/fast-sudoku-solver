include_directories(inc)

set(SUDOKU_LIB_SRCS board.cpp)

add_library(sudokuLib STATIC ${SUDOKU_LIB_SRCS})
