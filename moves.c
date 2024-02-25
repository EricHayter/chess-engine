#include "moves.h"
#include "movelist.h"
#include "board.h"
#include <stdlib.h>
#include <assert.h>


Move *create_move(BoardPosition to, BoardPosition from, MoveFlag type)
{
    Move *move = malloc(sizeof(Move));
    if (!move) { // this is bad but we will keep it for now
        return NULL; 
    }

    move->to = to;
    move->from = from;
    move->type = type;
    return move;
}

// really not optimal but works for now
unsigned int LSB(BitBoard board)
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
unsigned int MSB(BitBoard board)
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
        if (direction > 0) // moving up or west
            nearest_blocker = MSB(blockers);
        else
            nearest_blocker = LSB(blockers);
        ray ^= get_ray(nearest_blocker, direction);
    }
    return ray;
}


BitBoard get_ray(BoardPosition start_pos, Direction direction)
{
    BitBoard ray = set_bit(0ull, start_pos);
    unsigned int pos = start_pos;
    int direction_value = direction;
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
        moves = set_bit(moves, position + NORTH);
    if (start & NOT_8_RANK & NOT_A_FILE)
        moves = set_bit(moves, position + NORTH_WEST);
    if (start & NOT_8_RANK & NOT_H_FILE)
        moves = set_bit(moves, position + NORTH_EAST);

    // horizontal moves
    if (start & NOT_H_FILE)
        moves = set_bit(moves, position + EAST);
    if (start & NOT_A_FILE)
        moves = set_bit(moves, position + WEST);

    // south moves
    if (start & NOT_1_RANK)
        moves = set_bit(moves, position + SOUTH);
    if (start & NOT_1_RANK & NOT_A_FILE)
        moves = set_bit(moves, position + SOUTH_WEST);
    if (start & NOT_1_RANK & NOT_H_FILE)
        moves = set_bit(moves, position + SOUTH_EAST);

    return moves;
}


BitBoard knight_moves(Board* board, BoardPosition position)
{   
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = (BitBoard) 0ull;

    // north moves
    if (start & NOT_78_RANK & NOT_H_FILE) 
        moves = set_bit(moves, position + NORTH + NORTH_EAST);
    if (start & NOT_78_RANK & NOT_A_FILE) 
        moves = set_bit(moves, position + NORTH + NORTH_WEST);

    // east moves
    if (start & NOT_GH_FILE & NOT_8_RANK)
        moves = set_bit(moves, position + EAST + NORTH_EAST);
    if (start & NOT_GH_FILE & NOT_1_RANK)
        moves = set_bit(moves, position + EAST + SOUTH_EAST);

    // south moves
    if (start & NOT_12_RANK & NOT_H_FILE)
        moves = set_bit(moves, position + SOUTH + SOUTH_EAST);
    if (start & NOT_12_RANK & NOT_A_FILE)
        moves = set_bit(moves, position + SOUTH + SOUTH_WEST);

    // west moves
    if (start & NOT_AB_FILE & NOT_8_RANK)
        moves = set_bit(moves, position + WEST + NORTH_WEST);
    if (start & NOT_AB_FILE & NOT_1_RANK)
        moves = set_bit(moves, position + WEST + SOUTH_WEST);
 
    return moves;
}

BitBoard pawn_pushes(Board* board, BoardPosition position)
{
    Color to_move = board->turn;
    BitBoard occupied = get_occupied(board);
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = 0ull;

    switch (to_move) {
    case WHITE:
        if (start & FILE_2) 
            moves = set_bit(moves, position + 2 * NORTH);
        break;
    case BLACK:
        if (start & FILE_7) 
            moves = set_bit(moves, position + 2 * SOUTH);
        if (start & NOT_1_RANK)
            moves = set_bit(moves, position + SOUTH); 
        break;
    }
    
    return moves;
}

BitBoard pawn_attacks(Board* board, BoardPosition position)
{
    Color to_move = board->turn;
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = 0ull;

    switch (to_move) {
    case WHITE:
        if (start & NOT_8_RANK) {
            if (start & NOT_H_FILE)
                moves = set_bit(moves, position + NORTH_EAST);
            if (start & NOT_A_FILE)
                moves = set_bit(moves, position + NORTH_WEST);
        }
        break;
    case BLACK:
        if (start & NOT_1_RANK) {
            if (start & NOT_H_FILE)
                moves = set_bit(moves, position + SOUTH_EAST);
            if (start & NOT_A_FILE)
                moves = set_bit(moves, position + SOUTH_WEST);
        }
        break;
    }

    return moves;
}


BitBoard rook_moves(Board *board, BoardPosition position)
{
    BitBoard occupied = get_occupied(board);
    BitBoard moves = 0ull;
    moves |= get_ray_attacks(occupied, position, NORTH);
    moves |= get_ray_attacks(occupied, position, EAST);
    moves |= get_ray_attacks(occupied, position, SOUTH);
    moves |= get_ray_attacks(occupied, position, WEST);
    return moves;
}


BitBoard bishop_moves(Board* board, BoardPosition origin)
{
    BitBoard moves = 0ull;
    BitBoard occupied = get_occupied(board);

    moves |= get_ray_attacks(occupied, origin, NORTH_EAST);
    moves |= get_ray_attacks(occupied, origin, SOUTH_EAST);
    moves |= get_ray_attacks(occupied, origin, NORTH_WEST);
    moves |= get_ray_attacks(occupied, origin, SOUTH_WEST);

    return moves;
}


BitBoard queen_moves(Board* board, BoardPosition position)
{
    BitBoard occupied = get_occupied(board);
    return bishop_moves(occupied, position) | rook_moves(occupied, position);
}


// this silly
bool is_checked(Board* board) 
{
    unsigned int king_pos;
    switch (board->turn) {
    case WHITE:
        king_pos = LSB(board->wKing);
        if (queen_moves(board, king_pos) & board->bQueen) return true;
        if (rook_moves(board, king_pos) & board->bRook) return true;
        if (bishop_moves(board, king_pos) & board->bBishop) return true;
        if (knight_moves(king_pos) & board->bKnight) return true;
        if (pawn_attacks(king_pos, WHITE) & board->bPawn) return true;
        if (king_moves(king_pos) & board->bKing) return true;
        break;
    case BLACK:
        king_pos = LSB(board->bKing);
        if (queen_moves(board, king_pos) & board->wQueen) return true;
        if (rook_moves(board, king_pos) & board->wRook) return true;
        if (bishop_moves(board, king_pos) & board->wBishop) return true;
        if (knight_moves(king_pos) & board->wKnight) return true;
        if (king_moves(king_pos) & board->wKing) return true;
        break;
    }
    
    return false;
}

Board *make_move(Board* board, Move *move)
{
    // this can't be right at all idek why this is needed
    // create a copy of the board object before you do this
    // even editing just the friendly occupied would be OK

    BitBoard *pieceBoard;
    int from = move->from;
    if (board->wKing & (1 << from)) pieceBoard = &board->wKing;
    if (board->wQueen & (1 << from)) pieceBoard = &board->wQueen;
    if (board->wBishop & (1 << from)) pieceBoard = &board->wBishop;
    if (board->wKnight & (1 << from)) pieceBoard = &board->wKnight;
    if (board->wRook & (1 << from)) pieceBoard = &board->wRook;
    if (board->wPawn & (1 << from)) pieceBoard = &board->wPawn;

    if (board->wKing & (1 << from)) pieceBoard = &board->wKing;
    if (board->wQueen & (1 << from)) pieceBoard = &board->wQueen;
    if (board->wBishop & (1 << from)) pieceBoard = &board->wBishop;
    if (board->wKnight & (1 << from)) pieceBoard = &board->wKnight;
    if (board->wRook & (1 << from)) pieceBoard = &board->wRook;
    if (board->wPawn & (1 << from)) pieceBoard = &board->wPawn;
    
    *pieceBoard = reset_bit(*pieceBoard, move->from);
    *pieceBoard = set_bit(*pieceBoard, move->to);

    return NULL;
}
