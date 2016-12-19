#include "testUtils.hpp"

TEST_CASE("calculate_state_masks", "[board]") {
    for (int index = 0; index < SAMPLE_SUDOKU_ARRAY_SIZE; ++index) {
        Board board[1];
        parse_string_notation(SAMPLE_SUDOKU_ARRAY[index], board);
        calculate_state_masks(board);

        for (int digit = ONE; digit <= NINE; ++digit) {
            for (int square = 0; square < BOARD_SQUARE_COUNT; ++square) {
                bool square_set_actual = is_tri_rows_square_set(board->digit_state_masks[digit].tri_rows, square);

                bool square_set_expected = true;

                if (board->digit_at[square] != DIGIT_NONE && board->digit_at[square] != digit) {
                    square_set_expected = false;
                } else {
                    for (int sq = 0; sq < BOARD_SQUARE_COUNT; ++sq) {
                        if (conflict(square, sq) && board->digit_at[sq] == digit) {
                            square_set_expected = false;
                            break;
                        }
                    }
                }

                REQUIRE(square_set_expected == square_set_actual);
            }
        }
    }
}
