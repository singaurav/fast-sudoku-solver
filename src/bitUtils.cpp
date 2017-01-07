#include "bitUtils.hpp"

const int BitTable32 [32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};

const int BitTable64 [64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8
};

int pop_bit_32(BitBoard32 *bb) {
    int pos = BitTable32[((BitBoard32)(((*bb) & -(*bb)) * 0x077cb531u)) >> 27];
    *bb &= (*bb - 1);
    return pos;
}

int count_bits_32(BitBoard32 b) {
    int r;
    for (r = 0; b; r++, b &= b - 1);
    return r;
}

int pop_bit_64(BitBoard64 *bb) {
    BitBoard64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable64[(fold * 0x783a9b23) >> 26];
}
