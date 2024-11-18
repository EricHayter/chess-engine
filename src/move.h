#pragma once

#include "board.h"

typedef enum {
	QUIET_MOVE,
	DOUBLE_PAWN_PUSH,
	KING_CASTLE,
	QUEEN_CASTLE,
	CAPTURE,
	EP_CAPTURE, // en pessante capture
	KNIGHT_PROMO,
	BISHOP_PROMO,
	ROOK_PROMO,
	QUEEN_PROMO,
	KNIGHT_PROMO_CAP,
	BISHOP_PROMO_CAP,
	ROOK_PROMO_CAP,
	QUEEN_PROMO_CAP,
} MoveType;

typedef struct {
	Square to;
	Square from;
	MoveType mt;
} Move;
