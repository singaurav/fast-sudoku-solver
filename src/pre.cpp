#include "pre.hpp"
#include "boardData.hpp"
#include "bitUtils.hpp"
#include "io.hpp"

inline void flip_potential_locked_candidates_intersecs(int index, BitBoard64& intersecs, BitBoard64 processed_intersecs, BitBoard32 tri_rows[]) {
    for (int nn = 0; nn < INTERSEC_NEIGHBOURS_NEIGHBOURS_COUNT; ++nn) {
        int nn_index = INTERSEC_NEIGHBOURS_NEIGHBOURS[index][nn];
        BitBoard32 nn_mask = INTERSEC_MASKS[nn_index];

        int nn_tri_row_index = inter_mask_tri_row_index(nn_mask);
        BitBoard32 nn_tri_row_mask = inter_mask_tri_row_mask(nn_mask);

        if (tri_rows[nn_tri_row_index] & nn_tri_row_mask) {
            if ((processed_intersecs & (1ULL << nn_index)) == 0ULL) {
                intersecs |= (1ULL << nn_index);
            }
        }
    }
}

void digit_locked_candidates(BitBoard32 tri_rows[]) {
    BitBoard64 intersecs, processed_intersecs;

    intersecs = (1ULL << BOARD_INTERSEC_COUNT) - 1;
    processed_intersecs = 0ULL;

    while(intersecs) {
        int index = pop_bit_64(&intersecs);

        int tri_row_index = inter_mask_tri_row_index(INTERSEC_MASKS[index]);
        BitBoard32 tri_row_mask = inter_mask_tri_row_mask(INTERSEC_MASKS[index]);

        if (tri_rows[tri_row_index] & tri_row_mask) {
            BitBoard32 line_neighbour_1 = INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][0]];
            int ln_tri_row_index_1 = inter_mask_tri_row_index(line_neighbour_1);
            BitBoard32 ln_tri_row_mask_1 = inter_mask_tri_row_mask(line_neighbour_1);

            BitBoard32 line_neighbour_2 = INTERSEC_MASKS[INTERSEC_LINE_NEIGHBOURS[index][1]];
            int ln_tri_row_index_2 = inter_mask_tri_row_index(line_neighbour_2);
            BitBoard32 ln_tri_row_mask_2 = inter_mask_tri_row_mask(line_neighbour_2);

            BitBoard32 box_neighbour_1 = INTERSEC_MASKS[INTERSEC_BOX_NEIGHBOURS[index][0]];
            int bn_tri_row_index_1 = inter_mask_tri_row_index(box_neighbour_1);
            BitBoard32 bn_tri_row_mask_1 = inter_mask_tri_row_mask(box_neighbour_1);

            BitBoard32 box_neighbour_2 = INTERSEC_MASKS[INTERSEC_BOX_NEIGHBOURS[index][1]];
            int bn_tri_row_index_2 = inter_mask_tri_row_index(box_neighbour_2);
            BitBoard32 bn_tri_row_mask_2 = inter_mask_tri_row_mask(box_neighbour_2);

            if ((tri_rows[ln_tri_row_index_1] & ln_tri_row_mask_1) == 0UL &&
                (tri_rows[ln_tri_row_index_2] & ln_tri_row_mask_2) == 0UL) {
                if (tri_rows[bn_tri_row_index_1] & bn_tri_row_mask_1) {
                    tri_rows[bn_tri_row_index_1] &= ~bn_tri_row_mask_1;
                    processed_intersecs |= (1ULL << index);
                    flip_potential_locked_candidates_intersecs(index, intersecs, processed_intersecs, tri_rows);
                }

                if (tri_rows[bn_tri_row_index_2] & bn_tri_row_mask_2) {
                    tri_rows[bn_tri_row_index_2] &= ~bn_tri_row_mask_2;
                    processed_intersecs |= (1ULL << index);
                    flip_potential_locked_candidates_intersecs(index, intersecs, processed_intersecs, tri_rows);
                }
            } else if ((tri_rows[bn_tri_row_index_1] & bn_tri_row_mask_1) == 0UL &&
                (tri_rows[bn_tri_row_index_2] & bn_tri_row_mask_2) == 0UL) {
                if (tri_rows[ln_tri_row_index_1] & ln_tri_row_mask_1) {
                    tri_rows[ln_tri_row_index_1] &= ~ln_tri_row_mask_1;
                    processed_intersecs |= (1ULL << index);
                    flip_potential_locked_candidates_intersecs(index, intersecs, processed_intersecs, tri_rows);
                }

                if (tri_rows[ln_tri_row_index_2] & ln_tri_row_mask_2) {
                    tri_rows[ln_tri_row_index_2] &= ~ln_tri_row_mask_2;
                    processed_intersecs |= (1ULL << index);
                    flip_potential_locked_candidates_intersecs(index, intersecs, processed_intersecs, tri_rows);
                }
            }
        }
    }
}

void locked_candidates(Board* board) {
    for (int d = 0; d < DIGIT_COUNT; ++d) {
        digit_locked_candidates(board->digit_state_masks[d].tri_rows);
    }
}
