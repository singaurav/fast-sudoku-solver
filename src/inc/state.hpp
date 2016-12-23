#ifndef STATE_INCLUDED
#define STATE_INCLUDED

#include "boardData.hpp"
#include <list>

struct StateMask {
    BitBoard32 tri_rows[BOARD_TRI_ROW_COUNT];

    StateMask() {
        reset();
    }

    void reset() {
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

    BitBoard32 get_rank_bb(int rank) {
        return (tri_rows[TRI_ROW_FROM_RANK[rank]] & TRI_ROW_RANK_MASKS[rank]);
    }
};

struct State {
    BitBoard32 tri_rows[BOARD_TRI_ROW_COUNT];

    State(StateMask *state_mask) {
        tri_rows[0] = state_mask->tri_rows[0];
        tri_rows[1] = state_mask->tri_rows[1];
        tri_rows[2] = state_mask->tri_rows[2];
    }
};

struct StateList {
    std::list<State*> state_list;

    void reset() {
        std::list<State*>::const_iterator it;
        for (it = state_list.begin(); it != state_list.end(); ++it) {
            delete (*it);
        }

        state_list.clear();
    }
};

#endif // #ifndef STATE_INCLUDED
