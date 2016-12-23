#include "testUtils.hpp"

TEST_CASE("pop_bit", "[bitUtils]") {
    BitBoard32 bb = 1UL;
    REQUIRE(0 == pop_bit(&bb));
    REQUIRE(0UL == bb);

    bb = (1UL << 31);
    REQUIRE(31 == pop_bit(&bb));
    REQUIRE(0UL == bb);

    bb = ~(0UL);
    int bitPos = 0;
    while(bb) {
        REQUIRE(pop_bit(&bb) == bitPos++);
    }
}
