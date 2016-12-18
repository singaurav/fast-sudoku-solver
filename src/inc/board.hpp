#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include "boardData.hpp"
#include "state.hpp"

enum Digit : int {
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DIGIT_NONE
};

struct Board {
    int digit_at[BOARD_SQUARE_COUNT];

    StateMask digit_state_masks[DIGIT_COUNT];
};

void calculate_state_masks(Board *board);

#endif // #ifndef BOARD_INCLUDED
