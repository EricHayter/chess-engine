#include "attack_table.h"
#include "assert.h"
#include "board.h"

const Direction DIRECTIONS[NUM_DIRECTIONS] = {
	NORTH, NORTH_EAST, EAST, SOUTH_EAST, 
	SOUTH, SOUTH_WEST, WEST, NORTH_WEST
};

const int ROOK_DIRECTIONS[NUM_ROOK_DIRECTIONS] = {
	NORTH, EAST, SOUTH, WEST,	
};

const int BISHOP_DIRECTIONS[NUM_BISHOP_DIRECTIONS] = {
	NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST,	
};

const int KNIGHT_DIRECTIONS[NUM_KNIGHT_DIRECTIONS] = {
	NORTH + NORTH_EAST, NORTH + NORTH_WEST,
	EAST + NORTH_EAST, NORTH + SOUTH_EAST,	
	SOUTH + SOUTH_EAST, SOUTH + SOUTH_WEST,
	WEST + NORTH_WEST, NORTH + SOUTH_WEST	
};

int king_attacks_calculated = 0;
int queen_attacks_calculated = 0;
int bishop_attacks_calculated = 0;
int knight_attacks_calculated = 0;
int rook_attacks_calculated = 0;
int pawn_attacks_calculated = 0;

BitBoard KING_ATTACKS[NUM_SQUARES];
BitBoard QUEEN_ATTACKS[NUM_SQUARES][NUM_QUEEN_DIRECTIONS];
BitBoard BISHOP_ATTACKS[NUM_SQUARES][NUM_BISHOP_DIRECTIONS];
BitBoard KNIGHT_ATTACKS[NUM_SQUARES];
BitBoard ROOK_ATTACKS[NUM_SQUARES][NUM_ROOK_DIRECTIONS];
BitBoard PAWN_ATTACKS[NUM_COLORS][NUM_SQUARES];

int is_good_square(Square start, Square stop)
{
	return 
		stop < 64 &&
		stop >= 0 &&
		DISTANCES[start][stop] <= 2;
}

void init_attacks()
{
	init_distances();
	init_king_attacks();
	init_bishop_attacks();
	init_knight_attacks();
	init_rook_attacks();
	init_pawn_attacks();
	init_queen_attacks();
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
			Square end = start + DIRECTIONS[dir];	
			if (is_good_square(start, end))
				bb = set_square(bb, end);
		}	
		KING_ATTACKS[start] = bb;
	}
	king_attacks_calculated = 1;
}

void init_queen_attacks()
{
	// ensure that our distance lookup table is setup
	assert(distances_init);
	assert(bishop_attacks_calculated);
	assert(rook_attacks_calculated);
	if (queen_attacks_calculated)
		return;
	for (int i = 0; i < NUM_SQUARES; i++) {
		for (int dir_num = 0; dir_num < NUM_QUEEN_DIRECTIONS; dir_num++) {
			if (dir_num % 2)
				QUEEN_ATTACKS[i][dir_num] = BISHOP_ATTACKS[i][dir_num / 2];	
			else
				QUEEN_ATTACKS[i][dir_num] = ROOK_ATTACKS[i][dir_num / 2];	
		}	
	}

	queen_attacks_calculated = 1;
}

void init_bishop_attacks()
{
	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (bishop_attacks_calculated)
		return;

	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (rook_attacks_calculated)
		return;

	for (int start = 0; start < NUM_SQUARES; start++) {
		for (int dir_num = 0; dir_num < NUM_BISHOP_DIRECTIONS; dir_num++) {
			BitBoard bb = EMPTY_BOARD;
			Direction dir = BISHOP_DIRECTIONS[dir_num];
			Square pos = start;
			Square next_pos = start + dir;			
			while (is_good_square(pos, next_pos)) {
				bb = set_square(bb, next_pos);	
				pos = next_pos;
				next_pos += dir;
			}
			BISHOP_ATTACKS[start][dir_num] = bb;
		}	
	}
	bishop_attacks_calculated = 1;
}

void init_knight_attacks()
{

	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (pawn_attacks_calculated)
		return;

	for (int start = 0; start < NUM_SQUARES; start++) {
		BitBoard bb = EMPTY_BOARD;
		for (int dir = 0; dir < NUM_KNIGHT_DIRECTIONS; dir++) {
			Square stop = start + KNIGHT_DIRECTIONS[dir];
			if (is_good_square(start, stop))
				bb = set_square(bb, stop);
		}
		KNIGHT_ATTACKS[start] = bb;
	}
	knight_attacks_calculated = 1;
}

void init_rook_attacks()
{

	// ensure that our distance lookup table is setup
	assert(distances_init);
	if (rook_attacks_calculated)
		return;

	for (int start = 0; start < NUM_SQUARES; start++) {
		for (int dir_num = 0; dir_num < NUM_ROOK_DIRECTIONS; dir_num++) {
			BitBoard bb = EMPTY_BOARD;
			Direction dir = ROOK_DIRECTIONS[dir_num];
			Square pos = start;
			Square next_pos = start + dir;			
			while (is_good_square(pos, next_pos)) {
				bb = set_square(bb, next_pos);	
				pos = next_pos;
				next_pos += dir;
			}
			ROOK_ATTACKS[start][dir_num] = bb;
		}	
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
			bb = set_square(bb, start + SOUTH_EAST);
		if (is_good_square(start, start + SOUTH_WEST))
			bb = set_square(bb, start + SOUTH_WEST);
		PAWN_ATTACKS[BLACK][start] = bb;
	}

	// White pawns
	for (int start = 0; start < NUM_SQUARES; start++) {
		BitBoard bb = EMPTY_BOARD;
		if (is_good_square(start, start + NORTH_EAST))
			bb = set_square(bb, start + NORTH_EAST);
		if (is_good_square(start, start + NORTH_WEST))
			bb = set_square(bb, start + NORTH_WEST);
		PAWN_ATTACKS[WHITE][start] = bb;
	}
	pawn_attacks_calculated = 1;
}

int lsb(BitBoard bb)
{
	assert(bb != EMPTY_BOARD);
	int i = 0;
	while (!(bb & 1ull)) {
		bb >>= 1;
		i++;
	}
	return i;
}

int msb(BitBoard bb)
{
	assert(bb != EMPTY_BOARD);
	int i = 63;
	while (!(bb & (1ull << 63))) {
		bb <<= 1;
		i--;
	}
	return i;
}
