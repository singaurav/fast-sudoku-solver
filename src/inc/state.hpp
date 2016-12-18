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
        for (int index = 0; index < BOARD_TRI_ROW_COUNT; ++index) {
            tri_rows[index] = (1UL << TRI_ROW_SQUARE_COUNT) - 1;
        }
    }

    void operator&=(const BitBoard32 mask_tri_rows[]) {
        for (int index = 0; index < BOARD_TRI_ROW_COUNT; ++index) {
            tri_rows[index] &= mask_tri_rows[index];
        }
    }

    void unmask_square(int square) {
        tri_rows[square / TRI_ROW_SQUARE_COUNT] &= (TRI_ROW_MASK & ~(1UL << (square % TRI_ROW_SQUARE_COUNT)));
    }
};

struct StateList {
    State states[DIGIT_STATES_MAX_COUNT];
    int count = 0;
};

#endif // #ifndef STATE_INCLUDED
