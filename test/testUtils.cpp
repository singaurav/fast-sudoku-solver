#include "testUtils.hpp"

bool conflict(int square_1, int square_2) {
    if (square_1 == square_2) {
        return false;
    }

    int rank_1 = square_1 / BOARD_RANK_COUNT;
    int file_1 = square_1 % BOARD_RANK_COUNT;

    int rank_2 = square_2 / BOARD_RANK_COUNT;
    int file_2 = square_2 % BOARD_RANK_COUNT;

    if (rank_1 == rank_2) {
        return true;
    }

    if (file_1 == file_2) {
        return true;
    }

    if (rank_1 / 3 == rank_2 / 3 && file_1 / 3 == file_2 / 3) {
        return true;
    }

    return false;
}
