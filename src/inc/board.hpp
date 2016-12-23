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
    StateList digit_state_lists[DIGIT_COUNT];
};

void calculate_state_masks(Board *board);
void calculate_digit_state_list(Board *board, int digit, StateMask *state_mask, int rank);
void calculate_state_lists(Board *board);
void reset_board(Board *board);

#endif // #ifndef BOARD_INCLUDED
