#pragma once

#include "board.h"

#define NUM_DIRECTIONS 8
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

#define NUM_KNIGHT_DIRECTIONS 8
#define NUM_QUEEN_DIRECTIONS 8
#define NUM_ROOK_DIRECTIONS 4
#define NUM_BISHOP_DIRECTIONS 4

extern const Direction DIRECTIONS[NUM_DIRECTIONS];

extern int king_attacks_calculated;
extern int queen_attacks_calculated;
extern int bishop_attacks_calculated;
extern int knight_attacks_calculated;
extern int rook_attacks_calculated;
extern int pawn_attacks_calculated;

// must index sliding piece attacks to simplify blocking pieces
extern BitBoard KING_ATTACKS[NUM_SQUARES];
extern BitBoard QUEEN_ATTACKS[NUM_SQUARES][NUM_QUEEN_DIRECTIONS];
extern BitBoard BISHOP_ATTACKS[NUM_SQUARES][NUM_BISHOP_DIRECTIONS];
extern BitBoard KNIGHT_ATTACKS[NUM_SQUARES];
extern BitBoard ROOK_ATTACKS[NUM_SQUARES][NUM_ROOK_DIRECTIONS];
extern BitBoard PAWN_ATTACKS[NUM_COLORS][NUM_SQUARES];

int is_good_square(Square start, Square stop);
void init_attacks();
void init_king_attacks();
void init_queen_attacks();
void init_bishop_attacks();
void init_knight_attacks();
void init_rook_attacks();
void init_pawn_attacks();

int lsb(BitBoard bb);
int msb(BitBoard bb);
