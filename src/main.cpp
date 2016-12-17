#include <iostream>

#include "board.hpp"
#include "io.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Welcome" << endl;

    Board board[1];

    for (int square = 0; square < BOARD_SQUARE_COUNT; ++square) {
        board->digit_at[square] = DIGIT_NONE;
    }

    print_board(board);
}
