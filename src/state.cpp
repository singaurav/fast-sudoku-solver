#include "state.hpp"

void solve(StateList state_lists[], SolveOutput *solve_output) {
    int sol_count = 0;
    int nodes_searched = 0;

    StateListPartitioned state_lists_p[DIGIT_COUNT];

    for (int index = 0; index < DIGIT_COUNT; ++index) {
        state_lists_p[index].set_first_partition(state_lists + index);
    }

    StateNode *zero, *one, *two, *three, *four, *five, *six, *seven;

    flip_min_size_partition(state_lists_p, 0);
    for (zero = state_lists_p[0].partitions[0]->beg; zero != nullptr; zero = zero->next) {
        partition(zero, state_lists_p, 1);
        flip_min_size_partition(state_lists_p, 1);

        for (one = state_lists_p[1].partitions[0]->beg; one != nullptr; one = one->next) {
            partition(one, state_lists_p, 2);
            flip_min_size_partition(state_lists_p, 2);

            for (two = state_lists_p[2].partitions[0]->beg; two != nullptr; two = two->next) {
                partition(two, state_lists_p, 3);
                flip_min_size_partition(state_lists_p, 3);

                for (three = state_lists_p[3].partitions[0]->beg; three != nullptr; three = three->next) {
                    partition(three, state_lists_p, 4);
                    flip_min_size_partition(state_lists_p, 4);

                    for (four = state_lists_p[4].partitions[0]->beg; four != nullptr; four = four->next) {
                        partition(four, state_lists_p, 5);
                        flip_min_size_partition(state_lists_p, 5);

                        for (five = state_lists_p[5].partitions[0]->beg; five != nullptr; five = five->next) {
                            partition(five, state_lists_p, 6);
                            flip_min_size_partition(state_lists_p, 6);

                            for (six = state_lists_p[6].partitions[0]->beg; six != nullptr; six = six->next) {
                                partition(six, state_lists_p, 7);
                                flip_min_size_partition(state_lists_p, 7);

                                for (seven = state_lists_p[7].partitions[0]->beg; seven != nullptr; seven = seven->next) {
                                    // solution found
                                    sol_count += 1;
                                    nodes_searched += 1;
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

    solve_output->sol_count = sol_count;
    solve_output->nodes_searched = nodes_searched;
}
