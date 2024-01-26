#include "moves.h"
#include "arraylist.h"
#include "board.h"
#include <assert.h>


int dir_num(Direction direction)
{
    switch (direction) {
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
        start_pos -= direction_value;
        ray = set_bit(ray, start_pos);
    }

    return ray;
}

BitBoard king_moves(BoardPosition position)
{   
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = (BitBoard) 0ull;

    // north moves
    if (start & NOT_8_RANK) moves = set_bit(moves, position - dir_num(NORTH));
    if (start & NOT_8_RANK & NOT_A_FILE) moves = set_bit(moves, position - dir_num(NORTH_WEST));
    if (start & NOT_8_RANK & NOT_H_FILE) moves = set_bit(moves, position - dir_num(NORTH_EAST));

    // horizontal moves
    if (start & NOT_H_FILE) moves = set_bit(moves, position - dir_num(EAST));
    if (start & NOT_A_FILE) moves = set_bit(moves, position - dir_num(WEST));

    // south moves
    if (start & NOT_1_RANK) moves = set_bit(moves, position - dir_num(SOUTH));
    if (start & NOT_1_RANK & NOT_A_FILE) moves = set_bit(moves, position - dir_num(SOUTH_WEST));
    if (start & NOT_1_RANK & NOT_H_FILE) moves = set_bit(moves, position - dir_num(SOUTH_EAST));

    return moves;
}

BitBoard knight_moves(BoardPosition position)
{   
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = (BitBoard) 0ull;

    // north moves
    if (start & NOT_78_RANK & NOT_H_FILE) moves = set_bit(moves, position - dir_num(NORTH) - dir_num(NORTH_EAST));
    if (start & NOT_78_RANK & NOT_A_FILE) moves = set_bit(moves, position - dir_num(NORTH) - dir_num(NORTH_WEST));

    // east moves
    if (start & NOT_GH_FILE & NOT_8_RANK) moves = set_bit(moves, position - dir_num(EAST) - dir_num(NORTH_EAST));
    if (start & NOT_GH_FILE & NOT_1_RANK) moves = set_bit(moves, position - dir_num(EAST) - dir_num(SOUTH_EAST));

    // south moves
    if (start & NOT_12_RANK & NOT_H_FILE) moves = set_bit(moves, position - dir_num(SOUTH) - dir_num(SOUTH_EAST));
    if (start & NOT_12_RANK & NOT_A_FILE) moves = set_bit(moves, position - dir_num(SOUTH) - dir_num(SOUTH_WEST));

    // west moves
    if (start & NOT_AB_FILE & NOT_8_RANK) moves = set_bit(moves, position - dir_num(WEST) - dir_num(NORTH_WEST));
    if (start & NOT_AB_FILE & NOT_1_RANK) moves = set_bit(moves, position - dir_num(WEST) - dir_num(SOUTH_WEST));
 
    return moves;
}
