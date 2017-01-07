#ifndef TEST_UTILS_INCLUDED
#define TEST_UTILS_INCLUDED

#include "catch.hpp"
#include "testData.hpp"

#include "bitUtils.hpp"
#include "board.hpp"
#include "boardData.hpp"
#include "io.hpp"
#include "pre.hpp"

bool conflict(int square_1, int square_2);
bool is_tri_rows_square_set(BitBoard32 tri_rows[], int square);

#endif // #ifndef TEST_UTILS_INCLUDED
