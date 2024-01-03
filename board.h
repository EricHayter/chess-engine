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

typedef enum {
    BISHOP,
    KING,
    KNIGHT,
    PAWN,
    QUEEN,
    ROOK,
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
    uint64_t doublePawnMove; // location of pawn that moved 2 squares
    uint64_t wKing;
    uint64_t wQueen;
    uint64_t wBishop;
    uint64_t wKnight;
    uint64_t wRook;
    uint64_t wPawn;
    uint64_t bKing;
    uint64_t bQueen;
    uint64_t bBishop;
    uint64_t bKnight;
    uint64_t bRook;
    uint64_t bPawn;
} Board;

typedef struct {
    PieceType pieceType;
    Color color;
} Piece;

int is_piece_equal(const Piece* piece1, const Piece* piece2);

extern const Piece EMPTY;

#endif
