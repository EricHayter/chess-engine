#include "moves.h"
#include "arraylist.h"
#include "board.h"


int direction_num(Direction dir)
{
    switch (dir) {
    case NORTH: return 8; 
    case NORTH_EAST: return 9; 
    case EAST: return 1; 
    case SOUTH_EAST: return -7; 
    case SOUTH: return -8; 
    case SOUTH_WEST: return -9; 
    case WEST: return -1; 
    case NORTH_WEST: return 7; 
    }
}


BitBoard get_ray(BoardPosition start_pos, Direction direction)
{
    BitBoard ray = (BitBoard) 0ull;
    BitBoard bounds;
    switch (direction) {
    case NORTH: 
        bounds = NOT_8_RANK;
        break;
    case NORTH_EAST:
        bounds = NOT_8_RANK & NOT_H_FILE;
        break;
    case EAST:
        bounds = NOT_H_FILE;
        break;
    case SOUTH_EAST:
        bounds = NOT_1_RANK & NOT_H_FILE;
        break;
    case SOUTH:
        bounds = NOT_1_RANK;
        break;
    case SOUTH_WEST:
        bounds = NOT_1_RANK & NOT_A_FILE;
        break;
    case WEST:
        bounds = NOT_A_FILE;
        break;
    case NORTH_WEST:
        bounds = NOT_8_RANK & NOT_A_FILE;
        break;
    }
    
    while (ray & bounds) {
            start_pos += direction;
            ray = set_bit(ray, start_pos);
    }

    return ray;
}

