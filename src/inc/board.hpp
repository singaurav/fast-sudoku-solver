#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <cstdint>

const int BOARD_SQUARE_COUNT = 81;
const int BOARD_RANK_COUNT = 9;
const int BOARD_FILE_COUNT = 9;

const int DIGIT_STATES_MAX_COUNT = 46656;

const int SQUARE_NONE = 81;

const int DIGIT_COUNT = 9;

typedef uint32_t BitBoard32;

enum Digit : int {
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DIGIT_NONE
};

struct DigitState {
    Digit digit;

    BitBoard32 ranks_123;
    BitBoard32 ranks_456;
    BitBoard32 ranks_789;
};

struct DigitStateList {
    Digit digit;

    DigitState states[DIGIT_STATES_MAX_COUNT];
    int count = 0;
};

struct Board {
    int digit_at[BOARD_SQUARE_COUNT] = {DIGIT_NONE};
};

#endif // #ifndef BOARD_INCLUDED
