#include "moves.h"
#include "assert.h"
#include "board.h"

const Direction DIRECTIONS[NUM_DIRECTIONS] = {
	NORTH, NORTH_EAST, EAST, SOUTH_EAST, 
	SOUTH, SOUTH_WEST, WEST, NORTH_WEST
};

int king_attacks_calculated = 0;
int queen_attacks_calculated = 0;
int bishop_attacks_calculated = 0;
int knight_attacks_calculated = 0;
int rook_attacks_calculated = 0;
int pawn_attacks_calculated = 0;

BitBoard KING_ATTACKS[NUM_SQUARES];
BitBoard QUEEN_ATTACKS[NUM_SQUARES];
BitBoard BISHOP_ATTACKS[NUM_SQUARES];
BitBoard KNIGHT_ATTACKS[NUM_SQUARES];
BitBoard ROOK_ATTACKS[NUM_SQUARES];
BitBoard PAWN_ATTACKS[NUM_COLORS][NUM_SQUARES];

int is_good_square(Position start, Position stop)
{
	return 
		stop < 64 &&
		stop >= 0 &&
		DISTANCES[start][stop] <= 2;
}

void init_king_attacks()
{
	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (king_attacks_calculated)
		return;

	for (int start = 0; start < NUM_SQUARES; start++) {
		BitBoard bb = EMPTY_BOARD;
		for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
			Position end = start + DIRECTIONS[dir];	
			if (is_good_square(start, end))
				bb = set_position(bb, end);
		}	
		KING_ATTACKS[start] = bb;
	}
	king_attacks_calculated = 1;
}

void init_queen_attacks()
{
	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (queen_attacks_calculated)
		return;
}

void init_bishop_attacks()
{
	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (bishop_attacks_calculated)
		return;
}

void init_knight_attacks()
{
	static const int KNIGHT_DIRECTIONS[NUM_KNIGHT_DIRECTIONS] = {
		NORTH + NORTH_EAST, NORTH + NORTH_WEST,
		EAST + NORTH_EAST, NORTH + SOUTH_EAST,	
		SOUTH + SOUTH_EAST, SOUTH + SOUTH_WEST,
		WEST + NORTH_WEST, NORTH + SOUTH_WEST	
	};

	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (pawn_attacks_calculated)
		return;

	for (int start = 0; start < NUM_SQUARES; start++) {
		BitBoard bb = EMPTY_BOARD;
		for (int dir = 0; dir < NUM_KNIGHT_DIRECTIONS; dir++) {
			Position stop = start + KNIGHT_DIRECTIONS[dir];
			if (is_good_square(start, stop))
				bb = set_position(bb, stop);
		}
		KNIGHT_ATTACKS[start] = bb;
	}
}

void init_rook_attacks()
{
	static const int ROOK_DIRECTIONS[NUM_ROOK_DIRECTIONS] = {
		NORTH, EAST, SOUTH, WEST,	
	};

	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (rook_attacks_calculated)
		return;

	for (int start = 0; start < NUM_SQUARES; start++) {
		BitBoard bb = EMPTY_BOARD;
		for (int dir_num = 0; dir_num < NUM_ROOK_DIRECTIONS; dir_num++) {
			Direction dir = ROOK_DIRECTIONS[dir_num];
			Position pos = start;
			Position next_pos = start + dir;			
			while (is_good_square(pos, next_pos)) {
				bb = set_position(bb, next_pos);	
				pos = next_pos;
				next_pos += dir;
			}
		}	
		ROOK_ATTACKS[start] = bb;
	}
	rook_attacks_calculated = 1;
}

void init_pawn_attacks()
{
	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (pawn_attacks_calculated)
		return;

	// Black pawns
	for (int start = 0; start < NUM_SQUARES; start++) {
		BitBoard bb = EMPTY_BOARD;
		if (is_good_square(start, start + SOUTH_EAST))
			bb = set_position(bb, start + SOUTH_EAST);
		if (is_good_square(start, start + SOUTH_WEST))
			bb = set_position(bb, start + SOUTH_WEST);
		PAWN_ATTACKS[BLACK][start] = bb;
	}

	// White pawns
	for (int start = 0; start < NUM_SQUARES; start++) {
		BitBoard bb = EMPTY_BOARD;
		if (is_good_square(start, start + NORTH_EAST))
			bb = set_position(bb, start + NORTH_EAST);
		if (is_good_square(start, start + NORTH_WEST))
			bb = set_position(bb, start + NORTH_WEST);
		PAWN_ATTACKS[WHITE][start] = bb;
	}
}

