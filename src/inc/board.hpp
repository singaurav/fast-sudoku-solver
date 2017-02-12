#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include "bitBoard.hpp"
#include "boardData.hpp"
#include "option.hpp"
#include "state.hpp"

enum Digit : int {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    DIGIT_NONE
};

struct Board {
    int digit_at[BOARD_SQUARE_COUNT];
    BitBoard81 digit_bit_boards[DIGIT_COUNT];

    BitBoard81 squares_solved;
    bool houses_solved[DIGIT_COUNT][HOUSE_COUNT];

    StateList digit_state_lists[DIGIT_COUNT];

    Board() : Board(BB81_ALL_ZERO) {}

    Board(const char *str) {
        for (int s = 0; s < BOARD_SQUARE_COUNT; ++s) {
            digit_at[s] = DIGIT_NONE;
        }

        for (int d = 0; d < 9; ++d) {
            digit_bit_boards[d] = BB81_ALL_ONE;
        }

        squares_solved = BB81_ALL_ZERO;

        for (int d = 0; d < 9; ++d) {
            for (int h = 0; h < 27; ++h) {
                houses_solved[d][h] = false;
            }
        }

        for (int s = 0; s < 81; ++s) {
            if (str[s] >= '1' && str[s] <= '9') {
                process_single(s, str[s] - '1');
            }
        }
    }

    void process_single(int square, int digit);
};

int process_naked_singles(Board &board);
int process_hidden_singles(Board &board);
void solve_singles(Board &board);

void calculate_digit_state_list(Board &board, int digit, BitBoard81 &mask,
                                int rank);
void calculate_state_lists(Board &board);
void reset_board(Board &board);
void solve(Board &board, SolveOutput *output, Option *opt);

#endif // #ifndef BOARD_INCLUDED
