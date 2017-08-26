#ifndef BIT_BOARD_INCLUDED
#define BIT_BOARD_INCLUDED

#include <initializer_list>
#include <iterator>
#include <cstdlib>

typedef uint32_t BitBoard32;

struct BitBoard81 {
    BitBoard32 bits27[3];

    BitBoard81(std::initializer_list<BitBoard32> il) {
        std::copy(il.begin(), il.end(), bits27);
    }

    BitBoard81(BitBoard32 b27[]) {
        bits27[0] = b27[0];
        bits27[1] = b27[1];
        bits27[2] = b27[2];
    }

    BitBoard81(const char *s) {
        for (int b = 0; b < 3; ++b) {
            bits27[b] = 0;
            for (int i = 0; i < 27; ++i) {
                if (s[b * 27 + i] == '1') {
                    bits27[b] |= (1UL << i);
                }
            }
        }
    }

    BitBoard81() { bits27[0] = bits27[1] = bits27[2] = 0UL; }

    bool is_square_set(int square) {
        return bits27[square / 27] & (1UL << (square % 27));
    }

    void set_square(int square) {
        bits27[square / 27] |= (1UL << (square % 27));
    }

    void unset_square(int square) {
        bits27[square / 27] &= 0x7FFFFFF & ~(1UL << (square % 27));
    }

    BitBoard81 operator&=(const BitBoard81 &rhs) {
        bits27[0] &= rhs.bits27[0];
        bits27[1] &= rhs.bits27[1];
        bits27[2] &= rhs.bits27[2];

        return *this;
    }

    BitBoard81 operator|=(const BitBoard81 &rhs) {
        bits27[0] |= rhs.bits27[0];
        bits27[1] |= rhs.bits27[1];
        bits27[2] |= rhs.bits27[2];

        return *this;
    }

    BitBoard81 operator^=(const BitBoard81 &rhs) {
        bits27[0] ^= rhs.bits27[0];
        bits27[1] ^= rhs.bits27[1];
        bits27[2] ^= rhs.bits27[2];

        return *this;
    }

    BitBoard81 operator&(const BitBoard81 &rhs) const {
        BitBoard32 b27[3];

        b27[0] = bits27[0] & rhs.bits27[0];
        b27[1] = bits27[1] & rhs.bits27[1];
        b27[2] = bits27[2] & rhs.bits27[2];

        return BitBoard81(b27);
    }

    BitBoard81 operator~() const {
        BitBoard32 b27[3];

        b27[0] = 0x7FFFFFF & ~bits27[0];
        b27[1] = 0x7FFFFFF & ~bits27[1];
        b27[2] = 0x7FFFFFF & ~bits27[2];

        return BitBoard81(b27);
    }

    explicit operator bool() const {
        return bits27[0] || bits27[1] || bits27[2];
    }
};

#endif // #ifndef BIT_BOARD_INCLUDED
