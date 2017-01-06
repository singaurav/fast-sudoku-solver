#include "pre.hpp"
#include "boardData.hpp"
#include "bitUtils.hpp"
#include "io.hpp"

void locked_candidates(Board* board) {
    BitBoard64 intersecs;

    for (int d = 0; d < DIGIT_COUNT; ++d) {
        intersecs = (1ULL << BOARD_INTERSEC_COUNT) - 1;

        while(intersecs) {
            int index = pop_bit_64(&intersecs);

            int tri_row_index = inter_mask_tri_row_index(INTERSEC_MASKS[index]);
            BitBoard32 tri_row_mask = inter_mask_tri_row_mask(INTERSEC_MASKS[index]);

            if (board->digit_state_masks[d].tri_rows[tri_row_index] & tri_row_mask) {
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

                if ((board->digit_state_masks[d].tri_rows[ln_tri_row_index_1] & ln_tri_row_mask_1) == 0UL &&
                    (board->digit_state_masks[d].tri_rows[ln_tri_row_index_2] & ln_tri_row_mask_2) == 0UL) {
                    if (board->digit_state_masks[d].tri_rows[bn_tri_row_index_1] & bn_tri_row_mask_1) {
                        board->digit_state_masks[d].tri_rows[bn_tri_row_index_1] &= ~bn_tri_row_mask_1;
                    }

                    if (board->digit_state_masks[d].tri_rows[bn_tri_row_index_2] & bn_tri_row_mask_2) {
                        board->digit_state_masks[d].tri_rows[bn_tri_row_index_2] &= ~bn_tri_row_mask_2;
                    }
                } else if ((board->digit_state_masks[d].tri_rows[bn_tri_row_index_1] & bn_tri_row_mask_1) == 0UL &&
                    (board->digit_state_masks[d].tri_rows[bn_tri_row_index_2] & bn_tri_row_mask_2) == 0UL) {
                    if (board->digit_state_masks[d].tri_rows[ln_tri_row_index_1] & ln_tri_row_mask_1) {
                        board->digit_state_masks[d].tri_rows[ln_tri_row_index_1] &= ~ln_tri_row_mask_1;
                    }

                    if (board->digit_state_masks[d].tri_rows[ln_tri_row_index_2] & ln_tri_row_mask_2) {
                        board->digit_state_masks[d].tri_rows[ln_tri_row_index_2] &= ~ln_tri_row_mask_2;
                    }
                }
            }
        }        
    }
}
