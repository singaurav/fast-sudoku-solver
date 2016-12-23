#include "bitUtils.hpp"
#include "board.hpp"
#include "boardData.hpp"
#include "state.hpp"

void calculate_state_masks(Board *board) {
    for (int square = 0; square < BOARD_SQUARE_COUNT; ++square) {
        int digit = board->digit_at[square];

        if (digit != DIGIT_NONE) {
            board->digit_state_masks[digit] &= SQUARE_CONFLICT_MASKS[square];

            for (int d = ONE; d <= NINE; ++d) {
                if (d != digit) {
                    board->digit_state_masks[d].unmask_square(square);
                }
            }
        }
    }
}

void calculate_digit_state_list(Board *board, int digit, StateMask *state_mask, int rank) {
    if (rank == DIGIT_COUNT) {
        board->digit_state_lists[digit].state_list.push_back(new State(state_mask));
    } else {
        BitBoard32 rank_bb = state_mask->get_rank_bb(rank) & board->digit_state_masks[digit].get_rank_bb(rank);

        while(rank_bb) {
            int square = TRI_ROW_SQUARE_COUNT * TRI_ROW_FROM_RANK[rank] + pop_bit(&rank_bb);

            BitBoard32 undo_tri_rows[BOARD_TRI_ROW_COUNT];
            undo_tri_rows[0] = state_mask->tri_rows[0] & SQUARE_TRUCE_MASKS[square][0];
            undo_tri_rows[1] = state_mask->tri_rows[1] & SQUARE_TRUCE_MASKS[square][1];
            undo_tri_rows[2] = state_mask->tri_rows[2] & SQUARE_TRUCE_MASKS[square][2];

            state_mask->tri_rows[0] &= SQUARE_CONFLICT_MASKS[square][0];
            state_mask->tri_rows[1] &= SQUARE_CONFLICT_MASKS[square][1];
            state_mask->tri_rows[2] &= SQUARE_CONFLICT_MASKS[square][2];

            calculate_digit_state_list(board, digit, state_mask, rank + 1);

            state_mask->tri_rows[0] |= undo_tri_rows[0];
            state_mask->tri_rows[1] |= undo_tri_rows[1];
            state_mask->tri_rows[2] |= undo_tri_rows[2];
        }
    }
}

void calculate_state_lists(Board *board) {
    for (int digit = ONE; digit <= NINE; ++digit) {
        StateMask state_mask;
        calculate_digit_state_list(board, digit, &state_mask, 0);
    }
}

void reset_board(Board *board) {
    for (int digit = ONE; digit <= NINE; ++digit) {
        board->digit_state_masks[digit].reset();
        board->digit_state_lists[digit].reset();
    }
}
