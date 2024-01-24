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

#endif
