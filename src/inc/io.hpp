#ifndef IO_INCLUDED
#define IO_INCLUDED

#include "board.hpp"
#include "boardData.hpp"

const char DIGIT_CHARS[DIGIT_COUNT + 1] = {'1', '2', '3', '4', '5',
                                           '6', '7', '8', '9', '.'};

char *get_string_notation(const Board &board);

#endif // #ifndef IO_INCLUDED
