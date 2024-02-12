#include "moves.h"
#include "board.h"
#include "arraylist.h"
#include <stdlib.h>
#include <assert.h>


Move *create_move(int to, int from, MoveFlag type)
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

BitBoard pawn_pushes(BoardPosition position, Color to_move)
{
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = 0ull;

    switch (to_move) {
    case WHITE:
        if (start & FILE_2) 
            moves = set_bit(moves, position + 2 * dir_num(NORTH));
        if (start & NOT_8_RANK)
            moves = set_bit(moves, position + dir_num(NORTH)); 
        break;
    case BLACK:
        if (start & FILE_7) 
            moves = set_bit(moves, position + 2 * dir_num(SOUTH));
        if (start & NOT_1_RANK)
            moves = set_bit(moves, position + dir_num(SOUTH)); 
        break;
    }
    
    return moves;
}

BitBoard pawn_attacks(BoardPosition position, Color to_move)
{
    BitBoard start = set_bit(0ull, position);
    BitBoard moves = 0ull;

    switch (to_move) {
    case WHITE:
        if (start & NOT_8_RANK) {
            if (start & NOT_H_FILE)
                moves = set_bit(moves, position + dir_num(NORTH_EAST));
            if (start & NOT_A_FILE)
                moves = set_bit(moves, position + dir_num(NORTH_WEST));
        }
        break;
    case BLACK:
        if (start & NOT_1_RANK) {
            if (start & NOT_H_FILE)
                moves = set_bit(moves, position + dir_num(SOUTH_EAST));
            if (start & NOT_A_FILE)
                moves = set_bit(moves, position + dir_num(SOUTH_WEST));
        }
        break;
    }

    return moves;
}


BitBoard rook_moves(BitBoard occupied, BoardPosition position)
{
    BitBoard moves = 0ull;
    moves |= get_ray_attacks(occupied, position, NORTH);
    moves |= get_ray_attacks(occupied, position, EAST);
    moves |= get_ray_attacks(occupied, position, SOUTH);
    moves |= get_ray_attacks(occupied, position, WEST);
    return moves;
}


BitBoard bishop_moves(BitBoard occupied, BoardPosition position)
{
    BitBoard moves = 0ull;
    moves |= get_ray_attacks(occupied, position, NORTH_EAST);
    moves |= get_ray_attacks(occupied, position, SOUTH_EAST);
    moves |= get_ray_attacks(occupied, position, NORTH_WEST);
    moves |= get_ray_attacks(occupied, position, SOUTH_WEST);
    return moves;
}


BitBoard queen_moves(BitBoard occupied, BoardPosition position)
{
    return bishop_moves(occupied, position) | rook_moves(occupied, position);
}


// this silly
bool is_checked(Board* board) 
{
    BitBoard occupied = get_occupied(board);
    unsigned int king_pos;
    switch (board->turn) {
    case WHITE:
        king_pos = bitscan_forward(board->wKing);
        if (queen_moves(occupied, king_pos) & board->bQueen) return true;
        if (rook_moves(occupied, king_pos) & board->bRook) return true;
        if (bishop_moves(occupied, king_pos) & board->bBishop) return true;
        if (knight_moves(king_pos) & board->bKnight) return true;
        if (pawn_attacks(king_pos, WHITE) & board->bPawn) return true;
        if (king_moves(king_pos) & board->bKing) return true;
        break;
    case BLACK:
        king_pos = bitscan_forward(board->bKing);
        if (queen_moves(occupied, king_pos) & board->wQueen) return true;
        if (rook_moves(occupied, king_pos) & board->wRook) return true;
        if (bishop_moves(occupied, king_pos) & board->wBishop) return true;
        if (knight_moves(king_pos) & board->wKnight) return true;
        if (king_moves(king_pos) & board->wKing) return true;
        break;
    }
    
    return false;
}

// Given a list of possible moves and the location of friendly and
// non-friendly pieces add move instances to the move_list arraylist.
void classify_moves(ArrayList *move_list, int original_pos, BitBoard moves, BitBoard vacant, BitBoard enemy)
{
    ArrayListError err;
    assert(!move_list);
    enemy |= moves;
    vacant |= moves;

    for (int square = 0; square < 64; square++) { // iterate through all the given possible moves
        if (enemy & (1 << square))
            arraylist_push(move_list, create_move(square, original_pos, CAPTURE));
        else if (vacant & (1 << square))
            arraylist_push(move_list, create_move(square, original_pos, QUIET_MOVE));
    }
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

ArrayList *get_moves(Board* board)
{
    BitBoard occupied = get_occupied(board);
    BitBoard vacant = get_vacant_squares(board);
    BitBoard white_pieces = get_white_pieces(board);
    BitBoard black_pieces = get_black_pieces(board);
    ArrayList* move_list = arraylist_create();

    switch (board->turn) {
    case WHITE:
        for (int square = 0; square < 64; square++) { // check each square for a white piece
            if (board->wKing >> square & 1) {
               classify_moves(move_list, square, 
                       king_moves(square), vacant, black_pieces);
               classify_moves(move_list, square, 
                       queen_moves(occupied, square), vacant, black_pieces);
               classify_moves(move_list, square, 
                       bishop_moves(occupied, square), vacant, black_pieces);
               classify_moves(move_list, square, 
                       knight_moves(square), vacant, black_pieces);
               classify_moves(move_list, square, 
                       rook_moves(occupied, square), vacant, black_pieces);
               // add extra edge cases (i.e. pawn promo, en pessant, castle)
            }
        }

        break;
    case BLACK:
        for (int square = 0; square < 64; square++) { // check each square for a white piece
            if (board->wKing >> square & 1) {
               classify_moves(move_list, square, 
                       king_moves(square), vacant, white_pieces);
               classify_moves(move_list, square, 
                       queen_moves(occupied, square), vacant, white_pieces);
               classify_moves(move_list, square, 
                       bishop_moves(occupied, square), vacant, white_pieces);
               classify_moves(move_list, square, 
                       knight_moves(square), vacant, white_pieces);
               classify_moves(move_list, square, 
                       rook_moves(occupied, square), vacant, white_pieces);
               // add extra edge cases (i.e. pawn promo, en pessant, castle)
            }
        }

        break;
    }

    return move_list;
}
