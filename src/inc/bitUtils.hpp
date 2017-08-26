#ifndef BIT_UTILS_INCLUDED
#define BIT_UTILS_INCLUDED

#include "bitBoard.hpp"

#if defined(__GNUC__)

inline int lsb(BitBoard32 bb) { return __builtin_ctzl(bb); }

#else

#define NO_BSF

const int BitTable32[32] = {0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20,
                            15, 25, 17, 4,  8,  31, 27, 13, 23, 21, 19,
                            16, 7,  26, 12, 18, 6,  11, 5,  10, 9};

inline int lsb(BitBoard32 bb) {
  return BitTable32[((uint32_t)((bb & -bb) * 0x077cb531u)) >> 27];
}

#endif

inline int pop_bit_32(BitBoard32 *bb) {
  int pos = lsb(*bb);
  *bb &= (*bb - 1);
  return pos;
}

inline int pop_bit_81(BitBoard81 *bb) {
  if (bb->bits27[0]) {
    return pop_bit_32(bb->bits27);
  } else if (bb->bits27[1]) {
    return 27 + pop_bit_32(bb->bits27 + 1);
  } else {
    return 54 + pop_bit_32(bb->bits27 + 2);
  }
}

inline int count_bits_32(BitBoard32 bb) {
  int r;
  for (r = 0; bb; r++, bb &= bb - 1)
    ;
  return r;
}

inline int count_bits_81(BitBoard81 bb) {
  return count_bits_32(bb.bits27[0]) + count_bits_32(bb.bits27[1]) +
         count_bits_32(bb.bits27[2]);
}

#endif // #ifndef BIT_UTILS_INCLUDED
