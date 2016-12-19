#include <iostream>
#include "io.hpp"

using namespace std;

void print_board(int board[], bool bit_mode) {
    cout << endl;

	string space = "    ";

	for (int print_r = 0; print_r < BOARD_RANK_COUNT + BOARD_TRI_ROW_COUNT + 1; ++print_r) {
		cout << space;

		if (print_r % (BOARD_TRI_ROW_COUNT + 1) == 0) {
			cout << "+-------+-------+-------+" << endl;
		} else {
			int board_r = print_r - print_r / (BOARD_TRI_ROW_COUNT + 1) - 1;

			for (int block_f = 0; block_f < 3; ++block_f) {
				cout << "| ";
				for (int board_f = 0; board_f < 3; ++board_f) {
                    int square = board_r * BOARD_FILE_COUNT + block_f * 3 + board_f;

                    if (bit_mode) {
                        cout << board[square] << " ";
                    } else {
					    cout << DIGIT_CHARS[board[square]] << " ";
                    }
				}
			}

			cout << "|" << endl;
		}
	}
}

void print_tri_rows_bb(BitBoard32 tri_rows[]) {
    int board[BOARD_SQUARE_COUNT];

    for (int index = 0; index < BOARD_TRI_ROW_COUNT; ++index) {
        BitBoard32 tri_row = tri_rows[index];

        for (int r = 0; r < 3; ++r) {
            for (int file = 0; file < BOARD_FILE_COUNT; ++file) {
                int tri_rows_square = r * BOARD_FILE_COUNT + file;
                int square = (index * 3 + r) * BOARD_FILE_COUNT + file;

                if ((tri_row & (1UL << tri_rows_square)) == 0UL) {
                    board[square] = 0;
                } else {
                    board[square] = 1;
                }
            }
        }
    }

    print_board(board, true);
}

void parse_string_notation(const char *sn, Board *board) {
    for (int square = 0; square < BOARD_SQUARE_COUNT; ++square) {
        board->digit_at[square] = sn[square] >= '1' && sn[square] <= '9' ? sn[square] - '1' : DIGIT_NONE;
    }
}
