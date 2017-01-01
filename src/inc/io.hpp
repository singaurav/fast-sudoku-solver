#ifndef IO_INCLUDED
#define IO_INCLUDED

#include "boardData.hpp"
#include "board.hpp"

const char DIGIT_CHARS[DIGIT_COUNT + 1] = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'
};

void print_board(int digit_at[], bool bit_mode);
void print_tri_rows_bb(BitBoard32 tri_rows[]);
void parse_string_notation(const char *sn, Board *board);
char* get_string_notation(const Board *board);

#endif // #ifndef IO_INCLUDED
