#include <iostream>
#include <stdio.h>
#include <string.h>

#include "board.hpp"
#include "io.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int buffer_size = 1024;
    char buffer[buffer_size];

    int square;
    Board board[1];

    while (fgets(buffer, buffer_size, stdin) != nullptr) {
        if (strlen(buffer) < BOARD_SQUARE_COUNT) {
            continue;
        }

        for (square = 0; square < BOARD_SQUARE_COUNT; ++square) {
            board->digit_at[square] = buffer[square] >= '1' && buffer[square] <= '9' ? buffer[square] - '1' : DIGIT_NONE;
        }

        print_board(board->digit_at, false);

        calculate_state_masks(board);

        for (int d = ONE; d <= NINE; ++d) {
            print_tri_rows_bb(board->digit_state_masks[d].tri_rows);
        }
    }
}
