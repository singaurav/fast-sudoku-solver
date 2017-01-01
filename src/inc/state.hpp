#ifndef STATE_INCLUDED
#define STATE_INCLUDED

#include "boardData.hpp"
#include "option.hpp"
#include "board.hpp"

struct StateMask {
    BitBoard32 tri_rows[BOARD_TRI_ROW_COUNT];

    StateMask() {
        reset();
    }

    void clear() {
        tri_rows[0] = 0UL;
        tri_rows[1] = 0UL;
        tri_rows[2] = 0UL;
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

    void operator^=(const BitBoard32 mask_tri_rows[]) {
        tri_rows[0] ^= mask_tri_rows[0];
        tri_rows[1] ^= mask_tri_rows[1];
        tri_rows[2] ^= mask_tri_rows[2];
    }

    void unmask_square(int square) {
        tri_rows[TRI_ROW_FROM_SQUARE[square]] &= (TRI_ROW_MASK & ~(1UL << (square % TRI_ROW_SQUARE_COUNT)));
    }

    BitBoard32 get_rank_bb(int rank) {
        return (tri_rows[TRI_ROW_FROM_RANK[rank]] & TRI_ROW_RANK_MASKS[rank]);
    }
};

struct StateNode {
    BitBoard32 tri_rows[BOARD_TRI_ROW_COUNT];
    int digit;
    StateNode* next;

    StateNode() {
        next = nullptr;
    }

    StateNode(StateMask *state_mask, int d) {
        digit = d;
        tri_rows[0] = state_mask->tri_rows[0];
        tri_rows[1] = state_mask->tri_rows[1];
        tri_rows[2] = state_mask->tri_rows[2];
        next = nullptr;
    }
};

struct StateList {
    StateNode *beg;
    StateNode *end;
    int size;

    StateList() {
        beg = end = nullptr;
        size = 0;
    }

    void add_state_node(StateNode *state_node) {
        if (size  < 1) {
            beg = end = state_node;
            size = 1;
        } else {
            end->next = state_node;
            end = state_node;
            size += 1;
        }
    }

    void add_state_list(StateList *state_list_other) {
        if (state_list_other->size > 0) {
            if (size < 1) {
                beg = state_list_other->beg;
                end = state_list_other->end;
                size = state_list_other->size;
            } else {
                end->next = state_list_other->beg;
                end = state_list_other->end;
                size += state_list_other->size;
            }
        }

        state_list_other->beg = nullptr;
        state_list_other->end = nullptr;
        state_list_other->size = 0;
    }

    void reset() {
        StateNode* it = beg;

        while (it != nullptr) {
            StateNode* next = it->next;
            delete it;
            it = next;
        }

        beg = end = nullptr;
        size = 0;
    }
};

struct StateListPartitioned {
    StateList* partitions[DIGIT_COUNT];

    StateListPartitioned() {
        for (int index = 0; index < DIGIT_COUNT; ++index) {
            partitions[index] = new StateList();
        }
    }

    void set_first_partition(StateList* state_list) {
        partitions[0] = state_list;
    }

    void reset() {
        for (int index = 0; index < DIGIT_COUNT; ++index) {
            delete partitions[index];
        }
    }
};

struct SolveOutput {
    int sol_count;
    int nodes_searched;
};

inline void flip_min_size_partition(StateListPartitioned state_lists[], int beg_index) {
    int min_size_index = -1;
    int min_size = 100000;

    for (int index = beg_index; index < DIGIT_COUNT; ++index) {
        if (state_lists[index].partitions[0]->size < min_size) {
            min_size = state_lists[index].partitions[0]->size;
            min_size_index = index;
        }
    }

    if (min_size_index != beg_index) {
        StateListPartitioned t = state_lists[min_size_index];
        state_lists[min_size_index] = state_lists[beg_index];
        state_lists[beg_index] = t;
    }
}

inline bool tri_row_conflict(BitBoard32 tri_rows1[], BitBoard32 tri_rows2[]) {
    return  (tri_rows1[0] & tri_rows2[0]) ||
            (tri_rows1[1] & tri_rows2[1]) ||
            (tri_rows1[2] & tri_rows2[2]);
}

inline void partition(StateNode *state, StateListPartitioned state_lists[], int beg_index) {
    for (int index = beg_index; index < DIGIT_COUNT; ++index) {
        if (state_lists[index].partitions[0]->size > 0) {
            StateNode* it1 = state_lists[index].partitions[0]->beg;
            StateNode* it2 = it1->next;

            while (it2 != nullptr) {
                if (tri_row_conflict(state->tri_rows, it2->tri_rows)) {
                    it1->next = it2->next;
                    it2->next = nullptr;
                    state_lists[index].partitions[beg_index]->add_state_node(it2);
                    it2 = it1->next;
                    state_lists[index].partitions[0]->size -= 1;
                } else {
                    it1 = it2;
                    it2 = it2->next;
                }
            }

            state_lists[index].partitions[0]->end = it1;

            if (tri_row_conflict(state->tri_rows, state_lists[index].partitions[0]->beg->tri_rows)) {
                StateNode* new_beg = state_lists[index].partitions[0]->beg->next;
                state_lists[index].partitions[0]->beg->next = nullptr;
                state_lists[index].partitions[beg_index]->add_state_node(state_lists[index].partitions[0]->beg);
                state_lists[index].partitions[0]->beg = new_beg;

                if (new_beg == nullptr) {
                    state_lists[index].partitions[0]->end = nullptr;
                }

                state_lists[index].partitions[0]->size -= 1;
            }
        }
    }
}

inline void attach(StateListPartitioned state_lists[], int beg_index) {
    for (int index = beg_index; index < DIGIT_COUNT; ++index) {
        state_lists[index].partitions[0]->add_state_list(state_lists[index].partitions[beg_index]);
    }
}

#endif // #ifndef STATE_INCLUDED
