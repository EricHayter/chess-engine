#ifndef MOVES_H
#define MOVES_H

#include "board.h"

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
    NORTH = -8,
    NORTH_EAST = -7,
    EAST = 1,
    SOUTH_EAST = 9,
    SOUTH = 8,
    SOUTH_WEST = 7,
    WEST = -1,
    NORTH_WEST = -9,
} Direction;

unsigned int LSB(BitBoard board);
unsigned int MSB(BitBoard board);
BitBoard get_ray(BoardPosition start_pos, Direction direction);

BitBoard get_ray_moves(BitBoard occupied, BoardPosition position, Direction direction);
BitBoard get_negative_ray_attacks(BitBoard occupied, BoardPosition position, Direction direction);
BitBoard get_positive_ray_attacks(BitBoard occupied, BoardPosition position, Direction direction);

Move *create_move(BoardPosition to, BoardPosition from, MoveFlag type);
BitBoard king_moves(BoardPosition position);
BitBoard queen_moves(Board *board, BoardPosition position);
BitBoard rook_moves(Board *board, BoardPosition position);
BitBoard bishop_moves(Board *board, BoardPosition position);
BitBoard knight_moves(Board* board, BoardPosition position);
BitBoard pawn_attacks(BoardPosition position, Color to_move);
BitBoard pawn_pushes(BoardPosition position, Color to_move);

#endif
