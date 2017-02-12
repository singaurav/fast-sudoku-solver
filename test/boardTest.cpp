#include "string.h"
#include "testUtils.hpp"

TEST_CASE("SINGLES", "[board]") {
    for (int i = 0; i < SAMPLE_SINGLES_SUDOKU_SIZE; ++i) {
        Board board = SAMPLE_SINGLES_SUDOKU_ARRAY[i][0];

        solve_singles(board);

        REQUIRE(0 == strcmp(get_string_notation(board),
                            SAMPLE_SINGLES_SUDOKU_ARRAY[i][1]));
    }
}
