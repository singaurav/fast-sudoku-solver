#ifndef IO_INCLUDED
#define IO_INCLUDED

#include "board.hpp"

const char DIGIT_CHARS[DIGIT_COUNT + 1] = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'
};

void print_board(const Board *pos);

#endif // #ifndef IO_INCLUDED
