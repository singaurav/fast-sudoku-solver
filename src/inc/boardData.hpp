#ifndef BOARD_DATA_INCLUDED
#define BOARD_DATA_INCLUDED

#include "bitBoard.hpp"

extern const char *BB81_ALL_ZERO;
extern const char *BB81_ALL_ONE;

const int BOARD_SQUARE_COUNT = 81;
const int BOARD_RANK_COUNT = 9;
const int BOARD_FILE_COUNT = 9;
const int DIGIT_COUNT = 9;
const int HOUSE_COUNT = 27;

extern const int RANK_HOUSE[BOARD_SQUARE_COUNT];
extern const int FILE_HOUSE[BOARD_SQUARE_COUNT];
extern const int BLOCK_HOUSE[BOARD_SQUARE_COUNT];

extern const BitBoard81 HOUSE_MASKS[HOUSE_COUNT];
extern const BitBoard81 SQUARE_TRUCE_MASKS[BOARD_SQUARE_COUNT];

#endif // #ifndef BOARD_DATA_INCLUDED
