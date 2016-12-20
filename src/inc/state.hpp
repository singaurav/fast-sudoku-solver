#ifndef STATE_INCLUDED
#define STATE_INCLUDED

#include "boardData.hpp"

const int DIGIT_STATES_MAX_COUNT = 46656;

struct State {
    BitBoard32 tri_rows[BOARD_TRI_ROW_COUNT];
};

struct StateMask {
    BitBoard32 tri_rows[BOARD_TRI_ROW_COUNT];

    StateMask() {
        tri_rows[0] = TRI_ROW_MASK;
        tri_rows[1] = TRI_ROW_MASK;
        tri_rows[2] = TRI_ROW_MASK;
    }

    void operator&=(const BitBoard32 mask_tri_rows[]) {
        tri_rows[0] &= mask_tri_rows[0];
        tri_rows[1] &= mask_tri_rows[1];
        tri_rows[2] &= mask_tri_rows[2];
    }

    void unmask_square(int square) {
        tri_rows[TRI_ROW_FROM_SQUARE[square]] &= (TRI_ROW_MASK & ~(1UL << (square % TRI_ROW_SQUARE_COUNT)));
    }
};

struct StateList {
    State states[DIGIT_STATES_MAX_COUNT];
    int count = 0;
};

#endif // #ifndef STATE_INCLUDED
