#include "io.hpp"
#include <iostream>

char *get_string_notation(const Board &board) {
    static char sn[BOARD_SQUARE_COUNT + 1];

    for (int s = 0; s < BOARD_SQUARE_COUNT; ++s) {
        sn[s] = DIGIT_CHARS[board.digit_at[s]];
    }

    sn[BOARD_SQUARE_COUNT] = '\0';

    return sn;
}
