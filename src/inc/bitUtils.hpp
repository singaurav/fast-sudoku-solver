#ifndef BIT_UTILS_INCLUDED
#define BIT_UTILS_INCLUDED

#include "bitBoard.hpp"

int pop_bit_32(BitBoard32 *bb);
int pop_bit_81(BitBoard81 *bb);
int count_bits_32(BitBoard32 bb);
int count_bits_81(BitBoard81 bb);

#endif // #ifndef BIT_UTILS_INCLUDED
