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

// really not optimal but works for now
unsigned int bitscan_forward(BitBoard board)
{
    assert(board != 0);
    unsigned int i = 0;
    while (!(board & 1)) {
        board >>= 1;
        i++;
    }
    return i;
}

// these are almost certainly too slow
unsigned int bitscan_backward(BitBoard board)
{
    assert(board != 0);
    unsigned int i = 0;
    while (board >>= 1)
        i++;
    return i;
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


BitBoard king_moves(BoardPosition position)
{   
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = (BitBoard) 0ull;

    // north moves
    if (start & NOT_8_RANK)
        moves = set_bit(moves, position + dir_num(NORTH));
    if (start & NOT_8_RANK & NOT_A_FILE)
        moves = set_bit(moves, position + dir_num(NORTH_WEST));
    if (start & NOT_8_RANK & NOT_H_FILE)
        moves = set_bit(moves, position + dir_num(NORTH_EAST));

    // horizontal moves
    if (start & NOT_H_FILE)
        moves = set_bit(moves, position + dir_num(EAST));
    if (start & NOT_A_FILE)
        moves = set_bit(moves, position + dir_num(WEST));

    // south moves
    if (start & NOT_1_RANK)
        moves = set_bit(moves, position + dir_num(SOUTH));
    if (start & NOT_1_RANK & NOT_A_FILE)
        moves = set_bit(moves, position + dir_num(SOUTH_WEST));
    if (start & NOT_1_RANK & NOT_H_FILE)
        moves = set_bit(moves, position + dir_num(SOUTH_EAST));

    return moves;
}


BitBoard knight_moves(BoardPosition position)
{   
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = (BitBoard) 0ull;

    // north moves
    if (start & NOT_78_RANK & NOT_H_FILE) 
        moves = set_bit(moves, position + dir_num(NORTH) + dir_num(NORTH_EAST));
    if (start & NOT_78_RANK & NOT_A_FILE) 
        moves = set_bit(moves, position + dir_num(NORTH) + dir_num(NORTH_WEST));

    // east moves
    if (start & NOT_GH_FILE & NOT_8_RANK)
        moves = set_bit(moves, position + dir_num(EAST) + dir_num(NORTH_EAST));
    if (start & NOT_GH_FILE & NOT_1_RANK)
        moves = set_bit(moves, position + dir_num(EAST) + dir_num(SOUTH_EAST));

    // south moves
    if (start & NOT_12_RANK & NOT_H_FILE)
        moves = set_bit(moves, position + dir_num(SOUTH) + dir_num(SOUTH_EAST));
    if (start & NOT_12_RANK & NOT_A_FILE)
        moves = set_bit(moves, position + dir_num(SOUTH) + dir_num(SOUTH_WEST));

    // west moves
    if (start & NOT_AB_FILE & NOT_8_RANK)
        moves = set_bit(moves, position + dir_num(WEST) + dir_num(NORTH_WEST));
    if (start & NOT_AB_FILE & NOT_1_RANK)
        moves = set_bit(moves, position + dir_num(WEST) + dir_num(SOUTH_WEST));
 
    return moves;
}

bool is_checked(Board* board, Color side) // second param is already in board
{
    unsigned int king_position;
    if (side == WHITE)
        king_position = bitscan_forward(board->wKing);
    else if (side == BLACK)
        king_position = bitscan_forward(board->bKing);
    
    // queens
    // bishops
    // knights
    // rooks
    // pawns

}



BitBoard pawn_moves(BoardPosition position, Color to_move)
{
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = 0ull;

    switch (to_move) {
    case WHITE:
        if (start & FILE_2) 
            moves = set_bit(moves, position + 2 * dir_num(NORTH));
        if (start & NOT_8_RANK) {
            moves = set_bit(moves, position + dir_num(NORTH)); 
            if (start & NOT_H_FILE)
                moves = set_bit(moves, position + dir_num(NORTH_EAST));
            if (start & NOT_A_FILE)
                moves = set_bit(moves, position + dir_num(NORTH_WEST));
        }
        break;
    case BLACK:
        if (start & FILE_7) 
            moves = set_bit(moves, position + 2 * dir_num(SOUTH));
        if (start & NOT_1_RANK) {
            moves = set_bit(moves, position + dir_num(SOUTH)); 
            if (start & NOT_H_FILE)
                moves = set_bit(moves, position + dir_num(SOUTH_EAST));
            if (start & NOT_A_FILE)
                moves = set_bit(moves, position + dir_num(SOUTH_WEST));
        }
        break;
    }

    return moves;
}
