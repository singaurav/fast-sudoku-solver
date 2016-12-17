#include "testUtils.hpp"

TEST_CASE("square_conflict_masks", "[boardData]") {
    for (int square = 0; square < BOARD_SQUARE_COUNT; ++square) {
        BitBoard32 conflict_mask_tri_row[BOARD_TRI_ROW_COUNT];

        for (int tri_row_index = 0; tri_row_index < BOARD_TRI_ROW_COUNT; ++tri_row_index) {
            for (int square_2 = 0; square_2 < TRI_ROW_SQUARE_COUNT; ++square_2) {
                if (conflict(square, tri_row_index * TRI_ROW_SQUARE_COUNT + square_2)) {
                    REQUIRE((square_conflict_masks[square][tri_row_index] & (1UL << square_2)) == 0UL);
                } else {
                    REQUIRE((square_conflict_masks[square][tri_row_index] & (1UL << square_2)) != 0UL);
                }
            }
        }
    }
}
