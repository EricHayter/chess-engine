#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdbool.h>

#define NORTH 8
#define NORTH_EAST 9
#define EAST 1
#define SOUTH_EAST -7
#define SOUTH -8
#define SOUTH_WEST -9
#define WEST -1
#define NORTH_WEST 7

// TODO define files for the boarders
// 50 move draws
// castle should include both colors

typedef uint64_t BitBoard;

void bitboard_print(BitBoard board);

typedef enum {
    KING = 0,
    QUEEN = 1,
    BISHOP = 2,
    KNIGHT = 3,
    ROOK = 4,
    PAWN = 5,
    NONE_TYPE
} PieceType;

typedef enum {
    WHITE,
    BLACK,
    NONE_COLOR, // empty slots
} Color;

typedef struct {
    Color Turn;
    bool castleKSide;        // Can castle on king side
    bool castleQSide;        // Can castle of queen side
    BitBoard doublePawnMove; // location of pawn that moved 2 squares
    BitBoard wKing;
    BitBoard wQueen;
    BitBoard wBishop;
    BitBoard wKnight;
    BitBoard wRook;
    BitBoard wPawn;
    BitBoard bKing;
    BitBoard bQueen;
    BitBoard bBishop;
    BitBoard bKnight;
    BitBoard bRook;
    BitBoard bPawn;
} Board;

typedef struct {
    PieceType pieceType;
    Color color;
} Piece;

int is_piece_equal(const Piece* piece1, const Piece* piece2);

extern const Piece EMPTY;

#endif
