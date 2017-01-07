#include "testUtils.hpp"

TEST_CASE("locked_candidates", "[pre]") {
    const char* sample =
        "..1"       "111"       "..1"
        "..."       "11."       "..."
        "111"       "1.1"       "..."

        ".1."       "1.."       "1.."
        "1.."       "111"       ".11"
        "..."       "1.."       "..1"

        "1.1"       "..1"       "1.."
        "..1"       ".11"       "111"
        "111"       "..."       "111";

    BitBoard32 tri_rows[3];

    parse_string_notation_tri_rows(sample, tri_rows);

    digit_locked_candidates(tri_rows);

    REQUIRE((tri_rows[0] & (1UL << 2)) == 0UL);
    REQUIRE((tri_rows[0] & (1UL << 3)) == 0UL);
    REQUIRE((tri_rows[0] & (1UL << 4)) == 0UL);
    REQUIRE((tri_rows[0] & (1UL << 5)) == 0UL);
    REQUIRE((tri_rows[0] & (1UL << 21)) == 0UL);
    REQUIRE((tri_rows[0] & (1UL << 23)) == 0UL);
    REQUIRE(count_bits_32(tri_rows[0]) == 6);

    REQUIRE((tri_rows[1] & (1UL << 17)) == 0UL);
    REQUIRE((tri_rows[1] & (1UL << 26)) == 0UL);
    REQUIRE(count_bits_32(tri_rows[1]) == 9);

    REQUIRE((tri_rows[2] & (1UL << 17)) == 0UL);
    REQUIRE((tri_rows[2] & (1UL << 26)) == 0UL);
    REQUIRE(count_bits_32(tri_rows[2]) == 14);
}
