#include "bitUtils.hpp"

const int BitTable [32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};

int pop_bit(BitBoard32 *bb) {
    int pos = BitTable[((BitBoard32)(((*bb) & -(*bb)) * 0x077cb531u)) >> 27];
    *bb &= (*bb - 1);
    return pos;
}
