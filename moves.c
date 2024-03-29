#include "moves.h"
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


BitBoard king_moves(Board *board, BoardPosition position)
{   
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = 0ull;

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

    switch (board->turn) {
        case WHITE:
            // check white castling privileges on kingside
            break; 
        case BLACK:
            break;
    }

    return moves & ~get_friendly_squares(board);
}

BitBoard castling_moves(Board *board)
{
    BitBoard vacant = get_vacant_squares(board);
    BitBoard moves = 0ull;
    switch (board->turn) {
    case WHITE:
        if (board->castlingRights[wKingSide]) {
            if (!is_square_attacked(board, c1) &&
                    !is_square_attacked(board, d1) &&  
                    (~vacant & set_bit(0ull, c1)) &&
                    (~vacant & set_bit(0ull, d1)))
                moves |= set_bit(0ull, c1);
        }

        if (board->castlingRights[wQueenSide]) {
            if (!is_square_attacked(board, f1) &&
                    !is_square_attacked(board, g1) &&  
                    (~vacant & set_bit(0ull, f1)) &&
                    (~vacant & set_bit(0ull, g1)))
                moves |= set_bit(0ull, g1);
        }
        break;
    case BLACK:
        if (board->castlingRights[bKingSide]) {
            if (!is_square_attacked(board, c8) &&
                    !is_square_attacked(board, d8) &&  
                    (~vacant & set_bit(0ull, c8)) &&
                    (~vacant & set_bit(0ull, d8)))
                moves |= set_bit(0ull, c8);
        }

        if (board->castlingRights[bQueenSide]) {
            if (!is_square_attacked(board, f8) &&
                    !is_square_attacked(board, g8) &&  
                    (~vacant & set_bit(0ull, f8)) &&
                    (~vacant & set_bit(0ull, g8)))
                moves |= set_bit(0ull, g8);
        }
        break;
    }

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

    return moves & ~get_friendly_squares(board);
}

BitBoard pawn_pushes(Board* board, BoardPosition position)
{
    BitBoard moves = set_bit(0ull, position);
    BitBoard vacant = get_vacant_squares(board);
    BitBoard move;
    switch (board->turn) {
        case WHITE:
            move = set_bit(0ull, position + NORTH);
            if (move & vacant) {
                moves |= move;
                move = set_bit(0ull, position + 2 * NORTH);
                if (moves & RANK_2) // check if on right rank
                    moves |= move;
            }
            break;
        case BLACK:
            move = set_bit(0ull, position + SOUTH);
            if (move & vacant) {
                moves |= move;
                move = set_bit(0ull, position + 2 * SOUTH);
                if (moves & RANK_7) // check if on right rank
                    moves |= move;
            }
            break;
    }

    return moves & vacant; // piece needs to be located at origin in board
                           // otherwise kind of nasty bugs.
}

// PRECONDITION: pawns are never on the first or eighth rank
BitBoard pawn_attacks(Board* board, BoardPosition position)
{
    BitBoard attack_targets = get_enemy_squares(board);
    BitBoard moves = set_bit(0ull, position);
    switch (board->turn) {
        case WHITE:
            if (board->en_passant_square)
                attack_targets |= set_bit(0ull, board->en_passant_square + NORTH);
            if (moves & NOT_H_FILE)
                moves = set_bit(moves, position + NORTH_EAST);
            if (moves & NOT_A_FILE)
                moves = set_bit(moves, position + NORTH_WEST);
            break;
        case BLACK:
            if (board->en_passant_square)
                attack_targets |= set_bit(0ull, board->en_passant_square + SOUTH);
            if (moves & NOT_H_FILE)
                moves = set_bit(moves, position + SOUTH_EAST);
            if (moves & NOT_A_FILE)
                moves = set_bit(moves, position + SOUTH_WEST);
            break;
    }

    return moves & attack_targets;
}


BitBoard rook_moves(Board *board, BoardPosition position)
{
    BitBoard occupied = get_occupied_squares(board);
    BitBoard moves = 0ull;
    moves |= get_ray_attacks(occupied, position, NORTH);
    moves |= get_ray_attacks(occupied, position, EAST);
    moves |= get_ray_attacks(occupied, position, SOUTH);
    moves |= get_ray_attacks(occupied, position, WEST);
    return moves & ~get_friendly_squares(board);
}


BitBoard bishop_moves(Board* board, BoardPosition origin)
{
    BitBoard moves = 0ull;
    BitBoard occupied = get_occupied_squares(board);
    moves |= get_ray_attacks(occupied, origin, NORTH_EAST);
    moves |= get_ray_attacks(occupied, origin, SOUTH_EAST);
    moves |= get_ray_attacks(occupied, origin, NORTH_WEST);
    moves |= get_ray_attacks(occupied, origin, SOUTH_WEST);
    return moves & ~get_friendly_squares(board);
}


BitBoard queen_moves(Board* board, BoardPosition position)
{
    return bishop_moves(board, position) | rook_moves(board, position);
}

bool is_square_attacked(Board *board, BoardPosition pos)
{
    bool is_attacked = false;
    switch (board->turn) {
        case WHITE:
            board->turn = BLACK; // view possible attacks from black POV
            if (queen_moves(board, pos) & board->bQueen) is_attacked = true;
            else if (rook_moves(board, pos) & board->bRook) is_attacked = true;
            else if (bishop_moves(board, pos) & board->bBishop) is_attacked = true;
            else if (knight_moves(board, pos) & board->bKnight) is_attacked = true;
            else if (pawn_attacks(board, pos) & board->bPawn) is_attacked = true;
            else if (king_moves(board, pos) & board->bKing) is_attacked = true;
            board->turn = WHITE;
            break;
        case BLACK:
            board->turn = WHITE;
            if (queen_moves(board, pos) & board->wQueen) is_attacked = true;
            else if (rook_moves(board, pos) & board->wRook) is_attacked = true;
            else if (bishop_moves(board, pos) & board->wBishop) is_attacked = true;
            else if (knight_moves(board, pos) & board->wKnight) is_attacked = true;
            else if (pawn_attacks(board, pos) & board->wKing) is_attacked = true;
            else if (king_moves(board, pos) & board->wKing) is_attacked = true;
            board->turn = BLACK;
            break;
    }

    return is_attacked;
}

bool is_checked(Board* board) 
{
    BoardPosition king_pos;
    switch (board->turn) {
        case WHITE:
            king_pos = LSB(board->wKing);
            break;
        case BLACK:
            king_pos = LSB(board->bKing);
            break;
    }

    return is_square_attacked(board, king_pos);
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
