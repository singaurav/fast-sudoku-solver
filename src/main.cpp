#include <iostream>
#include <stdio.h>
#include <string.h>

#include "board.hpp"
#include "io.hpp"
#include "misc.hpp"
#include "option.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int buffer_size = 1024;
    char buffer[buffer_size];

    SolveOutput solve_output[1];
    Option option[1];

    if (!parse_command_line(argc, argv, option)) {
        return 1;
    }

    if (option->help) {
        return 0;
    }

    int count = 0;
    int count_one_sol = 0, count_multi_sol = 0, count_no_sol = 0;
    int start_time_ms = get_time_ms();

    while (fgets(buffer, buffer_size, option->fd) != nullptr) {
        if (strlen(buffer) < BOARD_SQUARE_COUNT) {
            continue;
        }

        Board board = buffer;

        solve_singles(board);
        calculate_state_lists(board);

        solve(board, solve_output, option);

        switch (solve_output->sol_count) {
        case 1:
            count_one_sol += 1;
            break;
        case 0:
            count_no_sol += 1;
            break;
        default:
            count_multi_sol += 1;
            break;
        }

        count += 1;
    }

    int time_taken_ms = get_time_ms() - start_time_ms;

    if (time_taken_ms < 1) {
        time_taken_ms = 1;
    }

    printf("   input puzzles > %d\n", count);
    printf(
        " puzzles by type > exactly one solution: %d, muliple solutions: %d, "
        "no solutions: %d\n",
        count_one_sol, count_multi_sol, count_no_sol);
    printf("  time takes(ms) > %d\n", time_taken_ms);
    printf(" puzzles per sec > %d\n", (count * 1000) / time_taken_ms);

    return 0;
}
