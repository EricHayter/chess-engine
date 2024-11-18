#pragma once

// Using a 64 bit word to represent occupancy
// MSB will represent H1 and LSB will be A8
typedef unsigned long long BitBoard;

#define EMPTY_BOARD 0ull

typedef enum {
	A8, B8, C8, D8, E8, F8, G8, H8,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A1, B1, C1, D1, E1, F1, G1, H1,
	NUM_SQUARES,
} Square;

typedef enum {
	WHITE,
	BLACK,
	NUM_COLORS
} Color;

typedef enum {
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN,
	NUM_PIECE_TYPES
} PieceType;

typedef struct {
	Color to_move;
	
	// occupancy for each piecetype and color
	BitBoard piece_occupancy[NUM_PIECE_TYPES * NUM_COLORS];	

	// total occupancy for each color
	BitBoard all_occupancy[NUM_COLORS];

	// Bitboard representing the vacant squares on the board
	BitBoard vacant_squares;

	// en pessant
	// castling
	// 50 move rule
} Game;

// What is the absolute distances between two positions?
extern int distances_init;
extern int DISTANCES[64][64];

// absolute value function
int abs(int x);
int max(int x, int y);
int row(Square p);
int col(Square p);
void init_distances();


BitBoard set_square(BitBoard bb, Square pos);
BitBoard clear_position(BitBoard bb, Square pos);

void board_print(BitBoard bb);
