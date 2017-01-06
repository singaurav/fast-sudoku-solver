#include "bitUtils.hpp"
#include "board.hpp"
#include "boardData.hpp"
#include "state.hpp"
#include "io.hpp"

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
        board->digit_state_lists[digit].add_state_node(new StateNode(state_mask, digit));
    } else {
        BitBoard32 rank_bb = state_mask->get_rank_bb(rank) & board->digit_state_masks[digit].get_rank_bb(rank);

        while(rank_bb) {
            int square = TRI_ROW_SQUARE_COUNT * TRI_ROW_FROM_RANK[rank] + pop_bit_32(&rank_bb);

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

void write_sol(StateNode* sol_states[], Board *board) {
    BitBoard32 last_digit_mask = 0x1ff;
    StateMask last_digit_state_mask;

    for (int index = 0; index < DIGIT_COUNT - 1; ++index) {
        for (int tri_row_index = 0; tri_row_index < 3; ++tri_row_index) {
            BitBoard32 tri_row = sol_states[index]->tri_rows[tri_row_index];

            while (tri_row) {
                int tri_row_square = pop_bit_32(&tri_row);
                board->digit_at[tri_row_index * TRI_ROW_SQUARE_COUNT + tri_row_square] = sol_states[index]->digit;
            }
        }

        last_digit_mask ^= (1UL << (sol_states[index]->digit));
        last_digit_state_mask ^= sol_states[index]->tri_rows;
    }

    int last_digit = pop_bit_32(&last_digit_mask);

    for (int tri_row_index = 0; tri_row_index < 3; ++tri_row_index) {
        BitBoard32 tri_row = last_digit_state_mask.tri_rows[tri_row_index];

        while (tri_row) {
            int tri_row_square = pop_bit_32(&tri_row);
            board->digit_at[tri_row_index * TRI_ROW_SQUARE_COUNT + tri_row_square] = last_digit;
        }
    }
}

void solve(Board *board, SolveOutput *solve_output, Option *option) {
    int sol_count = 0;
    int nodes_searched = 0;
    bool stop_search = false;

    StateListPartitioned state_lists_p[DIGIT_COUNT];

    for (int index = 0; index < DIGIT_COUNT; ++index) {
        state_lists_p[index].set_first_partition(board->digit_state_lists + index);
    }

    StateNode* sol_states[DIGIT_COUNT - 1];

    flip_min_size_partition(state_lists_p, 0);
    for (sol_states[0] = state_lists_p[0].partitions[0]->beg; sol_states[0] != nullptr && !stop_search; sol_states[0] = sol_states[0]->next) {
        partition(sol_states[0], state_lists_p, 1);
        flip_min_size_partition(state_lists_p, 1);

        for (sol_states[1] = state_lists_p[1].partitions[0]->beg; sol_states[1] != nullptr && !stop_search; sol_states[1] = sol_states[1]->next) {
            partition(sol_states[1], state_lists_p, 2);
            flip_min_size_partition(state_lists_p, 2);

            for (sol_states[2] = state_lists_p[2].partitions[0]->beg; sol_states[2] != nullptr && !stop_search; sol_states[2] = sol_states[2]->next) {
                partition(sol_states[2], state_lists_p, 3);
                flip_min_size_partition(state_lists_p, 3);

                for (sol_states[3] = state_lists_p[3].partitions[0]->beg; sol_states[3] != nullptr && !stop_search; sol_states[3] = sol_states[3]->next) {
                    partition(sol_states[3], state_lists_p, 4);
                    flip_min_size_partition(state_lists_p, 4);

                    for (sol_states[4] = state_lists_p[4].partitions[0]->beg; sol_states[4] != nullptr && !stop_search; sol_states[4] = sol_states[4]->next) {
                        partition(sol_states[4], state_lists_p, 5);
                        flip_min_size_partition(state_lists_p, 5);

                        for (sol_states[5] = state_lists_p[5].partitions[0]->beg; sol_states[5] != nullptr && !stop_search; sol_states[5] = sol_states[5]->next) {
                            partition(sol_states[5], state_lists_p, 6);
                            flip_min_size_partition(state_lists_p, 6);

                            for (sol_states[6] = state_lists_p[6].partitions[0]->beg; sol_states[6] != nullptr && !stop_search; sol_states[6] = sol_states[6]->next) {
                                partition(sol_states[6], state_lists_p, 7);
                                flip_min_size_partition(state_lists_p, 7);

                                for (sol_states[7] = state_lists_p[7].partitions[0]->beg; sol_states[7] != nullptr && !stop_search; sol_states[7] = sol_states[7]->next) {
                                    // solution found
                                    sol_count += 1;
                                    nodes_searched += 1;

                                    if (option->list_sol) {
                                        write_sol(sol_states, board);
                                        printf("%s\n", get_string_notation(board));
                                    }

                                    if (sol_count >= option->max_sol) {
                                        stop_search = true;
                                    }
                                }

                                attach(state_lists_p, 7);
                                nodes_searched += 1;
                            }

                            attach(state_lists_p, 6);
                            nodes_searched += 1;
                        }

                        attach(state_lists_p, 5);
                        nodes_searched += 1;
                    }

                    attach(state_lists_p, 4);
                    nodes_searched += 1;
                }

                attach(state_lists_p, 3);
                nodes_searched += 1;
            }

            attach(state_lists_p, 2);
            nodes_searched += 1;
        }

        attach(state_lists_p, 1);
        nodes_searched += 1;
    }

    if (option->count_sol) {
        printf("solution count: %d\n", sol_count);
    }

    if (option->list_sol || option->count_sol) {
        printf("\n");
    }

    solve_output->sol_count = sol_count;
    solve_output->nodes_searched = nodes_searched;

    for (int index = 0; index < DIGIT_COUNT; ++index) {
        state_lists_p[index].reset();
    }
}
