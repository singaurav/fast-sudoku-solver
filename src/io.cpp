#include <iostream>
#include "io.hpp"

using namespace std;

void print_board(const Board *pos) {
    cout << "Printing board:" << endl << endl;

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
					cout << DIGIT_CHARS[pos->digit_at[board_r * BOARD_FILE_COUNT + block_f * 3 + board_f]] << " ";
				}
			}

			cout << "|" << endl;
		}
	}
}
