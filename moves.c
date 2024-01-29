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
    while (board) {
        board <<= 1;
        i++;
    }
    return i;
}


BitBoard get_ray_attacks(BitBoard occupied, BoardPosition position, Direction direction)
{
    BitBoard ray = get_ray(position, direction);
    BitBoard blockers = occupied & ray;
    unsigned int nearest_blocker;
    if (blockers) {
        if (dir_num(direction) > 0) // moving up or west
            nearest_blocker = bitscan_backward(blockers);
        else
            nearest_blocker = bitscan_forward(blockers);
        ray ^= get_ray(nearest_blocker, direction);
    }
    return ray;
}


BitBoard get_ray(BoardPosition start_pos, Direction direction)
{
    BitBoard ray = set_bit(0ull, start_pos);
    unsigned int pos = start_pos;
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
        pos += direction_value;
        ray = set_bit(ray, pos);
    }
    ray = reset_bit(ray, start_pos);
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


BitBoard knight_attacks(BoardPosition position)
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


BitBoard rook_attacks(BitBoard occupied, BoardPosition position)
{
    BitBoard moves = 0ull;
    moves |= get_ray_attacks(occupied, position, NORTH);
    moves |= get_ray_attacks(occupied, position, EAST);
    moves |= get_ray_attacks(occupied, position, SOUTH);
    moves |= get_ray_attacks(occupied, position, WEST);
    return moves;
}


BitBoard bishop_attacks(BitBoard occupied, BoardPosition position)
{
    BitBoard moves = 0ull;
    moves |= get_ray_attacks(occupied, position, NORTH_EAST);
    moves |= get_ray_attacks(occupied, position, SOUTH_EAST);
    moves |= get_ray_attacks(occupied, position, NORTH_WEST);
    moves |= get_ray_attacks(occupied, position, SOUTH_WEST);
    return moves;
}

BitBoard queen_attacks(BitBoard occupied, BoardPosition position)
{
    return bishop_attacks(occupied, position) | rook_attacks(occupied, position);
}


bool is_checked(Board* board) 
{
    BitBoard occupied = get_occupied(board);
    unsigned int king_pos;
    if (board->turn == WHITE) {
        king_pos = bitscan_forward(board->wKing);
        if (queen_attacks(occupied, king_pos) & board->bQueen) return true;
        if (rook_attacks(occupied, king_pos) & board->bRook) return true;
        if (bishop_attacks(occupied, king_pos) & board->bBishop) return true;
        if (knight_attacks(king_pos) & board->bKnight) return true;
        // do a pawn check too
    } else {
        king_pos = bitscan_forward(board->bKing);
        if (queen_attacks(occupied, king_pos) & board->wQueen) return true;
        if (rook_attacks(occupied, king_pos) & board->wRook) return true;
        if (bishop_attacks(occupied, king_pos) & board->wBishop) return true;
        if (knight_attacks(king_pos) & board->wKnight) return true;
    }
    
    return false;
}

