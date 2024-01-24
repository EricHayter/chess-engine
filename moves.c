#include "moves.h"
#include "arraylist.h"
#include "board.h"
#include <assert.h>


int dir_num(Direction direction)
{
    switch (direction) {
    case NORTH: return -8; 
    case NORTH_EAST: return -7; 
    case EAST: return 1; 
    case SOUTH_EAST: return 9; 
    case SOUTH: return 8; 
    case SOUTH_WEST: return 7; 
    case WEST: return -1; 
    case NORTH_WEST: return -9; 
    }
}

BitBoard bitscan_forward(BitBoard board)
{
    assert(board != 0);
    return board ^ (board & (board - 1));
}

// try not to create the most ugly backwards bitscan challenge (impossible)
BitBoard bitscan_backward(BitBoard board)
{
    assert(board != 0); // XDDDDDDD
    while (board & (board - 1))
    {
        board = board & (board - 1); 
    }
    return bitscan_forward(board);
}


BitBoard get_ray(BoardPosition start_pos, Direction direction)
{
    BitBoard ray = (BitBoard) 0ull;
    int direction_value = dir_num(direction);
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
    
    while (!(ray & ~bounds)) {
        start_pos += direction_value;
        ray = set_bit(ray, start_pos);
    }

    return ray;
}

BitBoard knight_moves(BoardPosition position)
{   
    // got some bugs in here not sure what tho
    BitBoard board = (BitBoard) 0ull;
    // north moves
    if (position & NOT_78_RANK & NOT_H_FILE) board = set_bit(board, position + dir_num(NORTH) + dir_num(NORTH_EAST));
    if (position & NOT_78_RANK & NOT_A_FILE) board = set_bit(board, position + dir_num(NORTH) + dir_num(NORTH_WEST));

    // east moves
    if (position & NOT_GH_FILE & NOT_8_RANK) board = set_bit(board, position + dir_num(EAST) + dir_num(NORTH_EAST));
    if (position & NOT_GH_FILE & NOT_1_RANK) board = set_bit(board, position + dir_num(EAST) + dir_num(SOUTH_EAST));

    // south moves
    if (position & NOT_12_RANK & NOT_H_FILE) board = set_bit(board, position + dir_num(SOUTH) + dir_num(SOUTH_EAST));
    if (position & NOT_12_RANK & NOT_A_FILE) board = set_bit(board, position + dir_num(SOUTH) + dir_num(SOUTH_WEST));

    // west moves
    if (position & NOT_AB_FILE & NOT_8_RANK) board = set_bit(board, position + dir_num(WEST) + dir_num(NORTH_WEST));
    if (position & NOT_AB_FILE & NOT_1_RANK) board = set_bit(board, position + dir_num(WEST) + dir_num(SOUTH_WEST));
 
    return board;
}
