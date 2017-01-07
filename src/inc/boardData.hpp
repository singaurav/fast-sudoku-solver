#ifndef BOARD_DATA_INCLUDED
#define BOARD_DATA_INCLUDED

#include <cstdint>

const int BOARD_SQUARE_COUNT = 81;
const int BOARD_RANK_COUNT = 9;
const int BOARD_FILE_COUNT = 9;
const int BOARD_TRI_ROW_COUNT = 3;
const int TRI_ROW_SQUARE_COUNT = 27;
const int BOARD_INTERSEC_COUNT = 54;
const int INTERSEC_NEIGHBOUR_COUNT = 2;
const int INTERSEC_NEIGHBOURS_NEIGHBOURS_COUNT = 4;

const int SQUARE_NONE = 81;

const int DIGIT_COUNT = 9;

typedef uint32_t BitBoard32;
typedef uint64_t BitBoard64;

const BitBoard32 TRI_ROW_MASK = (1UL << TRI_ROW_SQUARE_COUNT) - 1;

extern const BitBoard32 SQUARE_CONFLICT_MASKS[BOARD_SQUARE_COUNT][BOARD_TRI_ROW_COUNT];
extern const BitBoard32 SQUARE_TRUCE_MASKS[BOARD_SQUARE_COUNT][BOARD_TRI_ROW_COUNT];

extern const int TRI_ROW_FROM_SQUARE[BOARD_SQUARE_COUNT];
extern const int TRI_ROW_FROM_RANK[BOARD_RANK_COUNT];
extern const BitBoard32 TRI_ROW_RANK_MASKS[BOARD_RANK_COUNT];
extern const BitBoard32 INTERSEC_MASKS[BOARD_INTERSEC_COUNT];
extern const int INTERSEC_LINE_NEIGHBOURS[BOARD_INTERSEC_COUNT][INTERSEC_NEIGHBOUR_COUNT];
extern const int INTERSEC_BOX_NEIGHBOURS[BOARD_INTERSEC_COUNT][INTERSEC_NEIGHBOUR_COUNT];
extern const int INTERSEC_NEIGHBOURS_NEIGHBOURS[BOARD_INTERSEC_COUNT][INTERSEC_NEIGHBOURS_NEIGHBOURS_COUNT];

inline int inter_mask_tri_row_index(BitBoard32 intersec_mask) {
    return intersec_mask >> TRI_ROW_SQUARE_COUNT;
}

inline BitBoard32 inter_mask_tri_row_mask(BitBoard32 intersec_mask) {
    return intersec_mask & TRI_ROW_MASK;
}

#endif // #ifndef BOARD_DATA_INCLUDED
