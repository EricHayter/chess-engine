#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

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

extern const Piece EMPTY;

#endif
