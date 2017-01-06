#include "testUtils.hpp"

TEST_CASE("SQUARE_CONFLICT_MASKS", "[boardData]") {
    for (int square = 0; square < BOARD_SQUARE_COUNT; ++square) {
        BitBoard32 conflict_mask_tri_row[BOARD_TRI_ROW_COUNT];

        for (int tri_row_index = 0; tri_row_index < BOARD_TRI_ROW_COUNT; ++tri_row_index) {
            for (int square_2 = 0; square_2 < TRI_ROW_SQUARE_COUNT; ++square_2) {
                if (conflict(square, tri_row_index * TRI_ROW_SQUARE_COUNT + square_2)) {
                    REQUIRE((SQUARE_CONFLICT_MASKS[square][tri_row_index] & (1UL << square_2)) == 0UL);
                } else {
                    REQUIRE((SQUARE_CONFLICT_MASKS[square][tri_row_index] & (1UL << square_2)) != 0UL);
                }
            }
        }
    }
}

TEST_CASE("SQUARE_TRUCE_MASKS", "[boardData]") {
    for (int square = 0; square < BOARD_SQUARE_COUNT; ++square) {
        BitBoard32 conflict_mask_tri_row[BOARD_TRI_ROW_COUNT];

        for (int tri_row_index = 0; tri_row_index < BOARD_TRI_ROW_COUNT; ++tri_row_index) {
            for (int square_2 = 0; square_2 < TRI_ROW_SQUARE_COUNT; ++square_2) {
                if (!conflict(square, tri_row_index * TRI_ROW_SQUARE_COUNT + square_2)) {
                    REQUIRE((SQUARE_TRUCE_MASKS[square][tri_row_index] & (1UL << square_2)) == 0UL);
                } else {
                    REQUIRE((SQUARE_TRUCE_MASKS[square][tri_row_index] & (1UL << square_2)) != 0UL);
                }
            }
        }
    }
}

TEST_CASE("TRI_ROW_FROM_SQUARE", "[boardData]") {
    for (int square = 0; square < BOARD_SQUARE_COUNT; ++square) {
        REQUIRE(TRI_ROW_FROM_SQUARE[square] == (square / TRI_ROW_SQUARE_COUNT));
    }
}

TEST_CASE("INTERSEC_MASKS", "[boardData]") {
    for (int tri_row_index = 0; tri_row_index < 3; ++tri_row_index) {
        for (int block = 0; block < 3; ++block) {
            for (int intersec_index = 0; intersec_index < 3; ++intersec_index) {
                BitBoard32 tri_row_mask = (tri_row_index << TRI_ROW_SQUARE_COUNT);

                BitBoard32 tri_square_h_mask = (0x00000007UL << (block * 3 + intersec_index * 9));
                BitBoard32 tri_square_v_mask = (0x00040201UL << (block * 3 + intersec_index));

                BitBoard32 intersec_h_mask = tri_row_mask | tri_square_h_mask;
                BitBoard32 intersec_v_mask = tri_row_mask | tri_square_v_mask;

                int h_count = 0;
                int v_count = 0;

                for (int h_find = 0; h_find < BOARD_INTERSEC_COUNT / 2; ++h_find) {
                    if (INTERSEC_MASKS[h_find] == intersec_h_mask) {
                        h_count += 1;
                    }
                }

                for (int v_find = BOARD_INTERSEC_COUNT / 2; v_find < BOARD_INTERSEC_COUNT; ++v_find) {
                    if (INTERSEC_MASKS[v_find] == intersec_v_mask) {
                        v_count += 1;
                    }
                }

                REQUIRE(1 == h_count);
                REQUIRE(inter_mask_tri_row_index(intersec_h_mask) == (tri_row_mask >>  TRI_ROW_SQUARE_COUNT));
                REQUIRE(inter_mask_tri_row_mask(intersec_h_mask) == tri_square_h_mask);

                REQUIRE(1 == v_count);
                REQUIRE(inter_mask_tri_row_index(intersec_v_mask) == (tri_row_mask >> TRI_ROW_SQUARE_COUNT));
                REQUIRE(inter_mask_tri_row_mask(intersec_v_mask) == tri_square_v_mask);
            }
        }
    }
}

TEST_CASE("INTERSEC_LINE_NEIGHBOURS", "[boardData]") {
    for (int index = 0; index < BOARD_INTERSEC_COUNT; ++index) {
        BitBoard32 tri_row_mask = inter_mask_tri_row_mask(INTERSEC_MASKS[index]);

        BitBoard32 neighbour_mask_1 = inter_mask_tri_row_mask(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][0]]);
        BitBoard32 neighbour_mask_2 = inter_mask_tri_row_mask(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][1]]);

        if (index < BOARD_INTERSEC_COUNT / 2) {
            REQUIRE(inter_mask_tri_row_index(INTERSEC_MASKS[index]) ==
                inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][0]]));
            REQUIRE(inter_mask_tri_row_index(INTERSEC_MASKS[index]) ==
                inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][1]]));
            REQUIRE(inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][0]]) ==
                inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][1]]));

            BitBoard32 all_mask = tri_row_mask | neighbour_mask_1 | neighbour_mask_2;

            BitBoard32 possible_masks[3] = {
                0x1ffUL, 0x1ffUL << 9, 0x1ffUL << 18
            };

            bool found = false;

            for (int f = 0; f < 3; ++f) {
                if (all_mask == possible_masks[f]) {
                    found = true;
                    break;
                }
            }

            REQUIRE(found);
        } else {
            REQUIRE(inter_mask_tri_row_index(INTERSEC_MASKS[index]) !=
                inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][0]]));
            REQUIRE(inter_mask_tri_row_index(INTERSEC_MASKS[index]) !=
                inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][1]]));
            REQUIRE(inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][0]]) !=
                inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][1]]));

            REQUIRE(tri_row_mask == neighbour_mask_1);
            REQUIRE(neighbour_mask_1 == neighbour_mask_2);
            REQUIRE(neighbour_mask_2 == tri_row_mask);
        }
    }
}

TEST_CASE("INTERSEC_BOX_NEIGHBOURS", "[boardData]") {
    for (int index = 0; index < BOARD_INTERSEC_COUNT; ++index) {
        BitBoard32 tri_row_mask = inter_mask_tri_row_mask(INTERSEC_MASKS[index]);

        BitBoard32 neighbour_mask_1 = inter_mask_tri_row_mask(INTERSEC_MASKS[INTERSEC_BOX_NEIGHBOURS[index][0]]);
        BitBoard32 neighbour_mask_2 = inter_mask_tri_row_mask(INTERSEC_MASKS[INTERSEC_BOX_NEIGHBOURS[index][1]]);

        REQUIRE(inter_mask_tri_row_index(INTERSEC_MASKS[index]) ==
            inter_mask_tri_row_index(INTERSEC_MASKS[INTERSEC_BOX_NEIGHBOURS[index][0]]));

        BitBoard32 all_mask = tri_row_mask | neighbour_mask_1 | neighbour_mask_2;

        BitBoard32 possible_masks[3] = {
            0x1c0e07UL, 0x1c0e07UL << 3, 0x1c0e07UL << 6
        };

        bool found = false;

        for (int f = 0; f < 3; ++f) {
            if (all_mask == possible_masks[f]) {
                found = true;
                break;
            }
        }

        REQUIRE(found);
    }
}
