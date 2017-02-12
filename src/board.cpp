#include "board.hpp"
#include "bitUtils.hpp"
#include "io.hpp"

void Board::process_single(int square, int digit) {
    digit_at[square] = digit;
    squares_solved.set_square(square);
    houses_solved[digit][RANK_HOUSE[square]] = true;
    houses_solved[digit][FILE_HOUSE[square]] = true;
    houses_solved[digit][BLOCK_HOUSE[square]] = true;

    for (int d = 0; d < 9; ++d) {
        if (d != digit) {
            digit_bit_boards[d].unset_square(square);
        } else {
            digit_bit_boards[digit].set_square(square);
        }
    }

    digit_bit_boards[digit] &= SQUARE_TRUCE_MASKS[square];
}

int process_naked_singles(Board &b) {
    BitBoard81 at_least_once = BB81_ALL_ZERO;
    BitBoard81 more_than_once = BB81_ALL_ZERO;
    BitBoard81 mask;

    for (int d = 0; d < 9; ++d) {
        mask = b.digit_bit_boards[d];
        more_than_once |= at_least_once & mask;
        at_least_once |= mask;
    }

    BitBoard81 naked_singles =
        (at_least_once & ~more_than_once) & ~b.squares_solved;

    int count = 0;

    while (naked_singles) {
        int square = pop_bit_81(&naked_singles);

        int digit = DIGIT_NONE;

        for (int d = 0; d < 9; ++d) {
            if (b.digit_bit_boards[d].is_square_set(square)) {
                digit = d;
                break;
            }
        }

        b.process_single(square, digit);

        count += 1;
    }

    return count;
}

int process_hidden_singles(Board &b) {
    int count = 0;
    for (int d = 0; d < 9; ++d) {
        for (int h = 0; h < 27; ++h) {
            if (!b.houses_solved[d][h]) {
                BitBoard81 mask = HOUSE_MASKS[h] & b.digit_bit_boards[d];
                if (1 == count_bits_81(mask)) {
                    int square = pop_bit_81(&mask);
                    b.process_single(square, d);

                    count += 1;
                }
            }
        }
    }

    return count;
}

void solve_singles(Board &board) {
    while (process_naked_singles(board) || process_hidden_singles(board)) {
    }
}

void calculate_digit_state_list(Board &board, int digit, BitBoard81 &mask,
                                int rank) {
    if (rank == DIGIT_COUNT) {
        board.digit_state_lists[digit].add_state_node(
            new StateNode(mask, digit));
    } else {
        BitBoard81 rank_bb =
            mask & HOUSE_MASKS[rank] & board.digit_bit_boards[digit];

        while (rank_bb) {
            int square = pop_bit_81(&rank_bb);

            BitBoard81 undo_mask = mask & ~SQUARE_TRUCE_MASKS[square];

            mask &= SQUARE_TRUCE_MASKS[square];

            calculate_digit_state_list(board, digit, mask, rank + 1);

            mask |= undo_mask;
        }
    }
}

void calculate_state_lists(Board &board) {
    for (int d = ONE; d <= NINE; ++d) {
        BitBoard81 mask = {0x7FFFFFF, 0x7FFFFFF, 0x7FFFFFF};
        calculate_digit_state_list(board, d, mask, 0);
    }
}

void reset_board(Board &board) {
    for (int d = ONE; d <= NINE; ++d) {
        board.digit_state_lists[d].reset();
    }
}

void write_sol(StateNode *sol_states[], Board &board) {
    BitBoard32 last_digit_mask = 0x1ff;
    BitBoard81 last_digit_state_mask;

    for (int i = 0; i < DIGIT_COUNT - 1; ++i) {
        BitBoard81 state_mask = sol_states[i]->state;

        while (state_mask) {
            int square = pop_bit_81(&state_mask);
            board.digit_at[square] = sol_states[i]->digit;
        }

        last_digit_mask ^= (1UL << (sol_states[i]->digit));
        last_digit_state_mask ^= sol_states[i]->state;
    }

    int last_digit = pop_bit_32(&last_digit_mask);

    while (last_digit_state_mask) {
        int square = pop_bit_81(&last_digit_state_mask);
        board.digit_at[square] = last_digit;
    }
}

void solve(Board &board, SolveOutput *output, Option *opt) {
    int sol_count = 0;
    int nodes_searched = 0;
    bool stop_search = false;

    StateListPartitioned lists_p[DIGIT_COUNT];

    for (int i = 0; i < DIGIT_COUNT; ++i) {
        lists_p[i].set_first_part(board.digit_state_lists + i);
    }

    StateNode *sol_states[DIGIT_COUNT - 1];

    flip_min_size_part(lists_p, 0);
    for (sol_states[0] = lists_p[0].parts[0]->beg;
         sol_states[0] != nullptr && !stop_search;
         sol_states[0] = sol_states[0]->next) {
        partition(sol_states[0], lists_p, 1);
        flip_min_size_part(lists_p, 1);

        for (sol_states[1] = lists_p[1].parts[0]->beg;
             sol_states[1] != nullptr && !stop_search;
             sol_states[1] = sol_states[1]->next) {
            partition(sol_states[1], lists_p, 2);
            flip_min_size_part(lists_p, 2);

            for (sol_states[2] = lists_p[2].parts[0]->beg;
                 sol_states[2] != nullptr && !stop_search;
                 sol_states[2] = sol_states[2]->next) {
                partition(sol_states[2], lists_p, 3);
                flip_min_size_part(lists_p, 3);

                for (sol_states[3] = lists_p[3].parts[0]->beg;
                     sol_states[3] != nullptr && !stop_search;
                     sol_states[3] = sol_states[3]->next) {
                    partition(sol_states[3], lists_p, 4);
                    flip_min_size_part(lists_p, 4);

                    for (sol_states[4] = lists_p[4].parts[0]->beg;
                         sol_states[4] != nullptr && !stop_search;
                         sol_states[4] = sol_states[4]->next) {
                        partition(sol_states[4], lists_p, 5);
                        flip_min_size_part(lists_p, 5);

                        for (sol_states[5] = lists_p[5].parts[0]->beg;
                             sol_states[5] != nullptr && !stop_search;
                             sol_states[5] = sol_states[5]->next) {
                            partition(sol_states[5], lists_p, 6);
                            flip_min_size_part(lists_p, 6);

                            for (sol_states[6] = lists_p[6].parts[0]->beg;
                                 sol_states[6] != nullptr && !stop_search;
                                 sol_states[6] = sol_states[6]->next) {
                                partition(sol_states[6], lists_p, 7);
                                flip_min_size_part(lists_p, 7);

                                for (sol_states[7] = lists_p[7].parts[0]->beg;
                                     sol_states[7] != nullptr && !stop_search;
                                     sol_states[7] = sol_states[7]->next) {
                                    // solution found
                                    sol_count += 1;
                                    nodes_searched += 1;

                                    if (opt->list_sol) {
                                        write_sol(sol_states, board);
                                        printf("%s\n",
                                               get_string_notation(board));
                                    }

                                    if (sol_count >= opt->max_sol) {
                                        stop_search = true;
                                    }
                                }

                                attach(lists_p, 7);
                                nodes_searched += 1;
                            }

                            attach(lists_p, 6);
                            nodes_searched += 1;
                        }

                        attach(lists_p, 5);
                        nodes_searched += 1;
                    }

                    attach(lists_p, 4);
                    nodes_searched += 1;
                }

                attach(lists_p, 3);
                nodes_searched += 1;
            }

            attach(lists_p, 2);
            nodes_searched += 1;
        }

        attach(lists_p, 1);
        nodes_searched += 1;
    }

    if (opt->count_sol) {
        printf("solution count: %d\n", sol_count);
    }

    if (opt->list_sol || opt->count_sol) {
        printf("\n");
    }

    output->sol_count = sol_count;
    output->nodes_searched = nodes_searched;

    for (int i = 0; i < DIGIT_COUNT; ++i) {
        lists_p[i].reset();
    }
}
