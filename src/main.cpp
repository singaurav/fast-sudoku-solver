#include <iostream>
#include <stdio.h>
#include <string.h>

#include "board.hpp"
#include "io.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int buffer_size = 1024;
    char buffer[buffer_size];

    Board board[1];

    while (fgets(buffer, buffer_size, stdin) != nullptr) {
        if (strlen(buffer) < BOARD_SQUARE_COUNT) {
            continue;
        }

        parse_string_notation(buffer, board);
        calculate_state_masks(board);
        
        print_board(board->digit_at, false);

        for (int d = ONE; d <= NINE; ++d) {
            print_tri_rows_bb(board->digit_state_masks[d].tri_rows);
        }
    }
}
