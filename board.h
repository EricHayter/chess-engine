#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#define ROW 8

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
    uint8_t wKing;
    uint8_t wQueen;
    uint8_t wBishop;
    uint8_t wKnight;
    uint8_t wRook;
    uint8_t wPawn;
    uint8_t bKing;
    uint8_t bQueen;
    uint8_t bBishop;
    uint8_t bKnight;
    uint8_t bRook;
    uint8_t bPawn;
} Board;

typedef struct {
    PieceType pieceType;
    Color color;
} Piece;

int is_piece_equal(const Piece* piece1, const Piece* piece2);

extern const Piece EMPTY;

#endif
