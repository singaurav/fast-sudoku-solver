#include <iostream>
#include <stdio.h>
#include <string.h>

#include "board.hpp"
#include "misc.hpp"
#include "io.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    FILE *fd;

    int buffer_size = 1024;
    char buffer[buffer_size];

    Board board[1];
    SolveOutput solve_output[1];

    if (argc > 1) {
        fd = fopen(argv[1], "r");
		if (!fd) {
			printf("Error while reading: '%s'\n", argv[1]);
			return(1);
		}
	}
	else {
        fd = stdin;
    }

    int count = 0;
    int start_time_ms = get_time_ms();

    while (fgets(buffer, buffer_size, fd) != nullptr) {
        if (strlen(buffer) < BOARD_SQUARE_COUNT) {
            continue;
        }

        parse_string_notation(buffer, board);

        calculate_state_masks(board);
        calculate_state_lists(board);

        solve(board->digit_state_lists, solve_output);

        if (solve_output->sol_count != 1) {
            printf("More than one sol");
            return(1);
        }

        count += 1;
    }

    int time_taken_ms = get_time_ms() - start_time_ms;

    if(time_taken_ms < 1) {
        time_taken_ms = 1;
    }

    printf("           puzzles: %d\n", count);
    printf("    time takes(ms): %d\n", time_taken_ms);
    printf("puzzles per second: %d\n", (count * 1000) / time_taken_ms);
}
