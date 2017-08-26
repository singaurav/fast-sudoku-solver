#include "testUtils.hpp"
#include <iostream>

TEST_CASE("pop_bit_32", "[bitUtils]") {
    BitBoard32 bb = 1UL;
    REQUIRE(0 == pop_bit_32(&bb));
    REQUIRE(!bb);

    bb = (1UL << 31);
    REQUIRE(31 == pop_bit_32(&bb));
    REQUIRE(!bb);

    bb = 0xFFFFFFFF;
    int bit_pos = 0;
    while (bb) {
        REQUIRE(pop_bit_32(&bb) == bit_pos++);
    }

    REQUIRE(32 == bit_pos);
}

TEST_CASE("pop_bit_81", "[bitUtils]") {
    BitBoard81 bb = {1UL, 0UL, 0UL};
    REQUIRE(0 == pop_bit_81(&bb));

    BitBoard81 bb1 = {0x7FFFFFF, 0x7FFFFFF, 0x7FFFFFF};
    int bit_pos = 0;

    while (bb1) {
        REQUIRE(pop_bit_81(&bb1) == bit_pos++);
    }

    REQUIRE(81 == bit_pos);
}

TEST_CASE("count_bits_32", "[bitUtils]") {
    REQUIRE(0 == count_bits_32(0UL));
    REQUIRE(1 == count_bits_32(1UL << 5));
    REQUIRE(3 == count_bits_32(25UL));
    REQUIRE(32 == count_bits_32(0xFFFFFFFF));
}

TEST_CASE("count_bits_81", "[bitUtils]") {
    REQUIRE(0 == count_bits_81({0UL, 0UL, 0UL}));
    REQUIRE(1 == count_bits_81({0UL, 0UL, 1UL}));
    REQUIRE(5 == count_bits_81({8UL, 1025UL, 66UL}));
    REQUIRE(81 == count_bits_81({0x7FFFFFF, 0x7FFFFFF, 0x7FFFFFF}));
}
