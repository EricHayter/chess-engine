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

BitBoard get_ray_moves(BitBoard occupied, BoardPosition position, Direction direction);
BitBoard get_negative_ray_attacks(BitBoard occupied, BoardPosition position, Direction direction);
BitBoard get_positive_ray_attacks(BitBoard occupied, BoardPosition position, Direction direction);

BitBoard king_moves(BoardPosition position);
BitBoard queen_moves(BitBoard board, BoardPosition position);
BitBoard rook_moves(BitBoard board, BoardPosition position);
BitBoard bishop_moves(BitBoard occupied, BoardPosition position);
BitBoard queen_moves(BitBoard occupied, BoardPosition position);
BitBoard pawn_attacks(BoardPosition position, Color to_move);
BitBoard pawn_pushes(BoardPosition position, Color to_move);

#endif
