#include "board.hpp"
#include "boardData.hpp"

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
