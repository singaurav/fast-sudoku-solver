#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <cstdint>

const int BOARD_SQUARE_COUNT = 81;
const int BOARD_RANK_COUNT = 9;
const int BOARD_FILE_COUNT = 9;

const int DIGIT_STATES_MAX_COUNT = 46656;

typedef uint32_t BitBoard32;

enum Digit : int {
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DIGIT_NONE
};

struct DigitState {
    BitBoard32 ranks_123;
    BitBoard32 ranks_456;
    BitBoard32 ranks_789;
};

struct DigitStateList {
    DigitState states[DIGIT_STATES_MAX_COUNT];
    int count;
};

struct Board {
    int digit_at[BOARD_SQUARE_COUNT];
};

#endif // #ifndef BOARD_INCLUDED
