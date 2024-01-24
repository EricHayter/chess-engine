#ifndef MOVES_H
#define MOVES_H

#include "board.h"
#include "arraylist.h"

typedef enum {
    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST,
} Direction;

int direction_num(Direction dir);
BitBoard bitscan_forward(BitBoard board);
BitBoard bitscan_backward(BitBoard board);
BitBoard get_ray(BoardPosition start_pos, Direction direction);
BitBoard knight_moves(BoardPosition position);

#endif
