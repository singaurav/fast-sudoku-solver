#include "testUtils.hpp"

TEST_CASE("RANK_HOUSE", "[boardData]") {
    for (int s = 0; s < BOARD_SQUARE_COUNT; ++s) {
        REQUIRE(s / BOARD_RANK_COUNT == RANK_HOUSE[s]);
    }
}

TEST_CASE("FILE_HOUSE", "[boardData]") {
    for (int s = 0; s < BOARD_SQUARE_COUNT; ++s) {
        REQUIRE(9 + s % BOARD_RANK_COUNT == FILE_HOUSE[s]);
    }
}

TEST_CASE("BLOCK_HOUSE", "[boardData]") {
    for (int s = 0; s < BOARD_SQUARE_COUNT; ++s) {
        REQUIRE(18 + (s / 27) * 3 + ((s % 9) / 3) == BLOCK_HOUSE[s]);
    }
}

TEST_CASE("HOUSE_MASKS", "[boardData]") {
    for (int s = 0; s < BOARD_SQUARE_COUNT; ++s) {
        BitBoard81 r = HOUSE_MASKS[RANK_HOUSE[s]];
        BitBoard81 f = HOUSE_MASKS[FILE_HOUSE[s]];
        BitBoard81 b = HOUSE_MASKS[BLOCK_HOUSE[s]];

        REQUIRE(true == f.is_square_set(s));
        REQUIRE(true == r.is_square_set(s));
        REQUIRE(true == b.is_square_set(s));
    }
}

TEST_CASE("SQUARE_TRUCE_MASKS", "[boardData]") {
    for (int s = 0; s < BOARD_SQUARE_COUNT; ++s) {
        BitBoard81 mask = SQUARE_TRUCE_MASKS[s];
        for (int t = 0; t < BOARD_SQUARE_COUNT; ++t) {
            if (conflict(s, t)) {
                REQUIRE(false == mask.is_square_set(t));
            } else {
                REQUIRE(true == mask.is_square_set(t));
            }
        }
    }
}
