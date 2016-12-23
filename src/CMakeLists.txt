include_directories(inc)

set(SUDOKU_LIB_SRCS bitUtils.cpp board.cpp boardData.cpp io.cpp state.cpp)

add_library(sudokuLib STATIC ${SUDOKU_LIB_SRCS})

add_executable(sudoku ${SUDOKU_LIB_SRCS} main.cpp)
