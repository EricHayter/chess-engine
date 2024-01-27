#ifndef MOVES_H
#define MOVES_H

#include "board.h"
#include "arraylist.h"

typedef enum {
    QUIET_MOVE,
    DOUBLE_PAWN_PUSH,
    KING_CASTLE,
    QUEEN_CASTLE,
    CAPTURE,
    EP_CAPTURE, // en passant
    KNIGHT_PROMO,
    BISHOP_PROMO,
    ROOK_PROMO,
    QUEEN_PROMO,
    KNIGHT_PROMO_C,
    BISHOP_PROMO_C,
    ROOK_PROMO_C,
    QUEEN_PROMO_C,
}  MoveFlag;

typedef struct {
    int to;
    int from;
    MoveFlag type;
} Move;

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
unsigned int bitscan_forward(BitBoard board);
unsigned int bitscan_backward(BitBoard board);
BitBoard get_ray(BoardPosition start_pos, Direction direction);
BitBoard king_moves(BoardPosition position);
BitBoard knight_moves(BoardPosition position);
BitBoard pawn_moves(BoardPosition position, Color to_move);

#endif
