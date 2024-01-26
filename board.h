#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdbool.h>

typedef unsigned long long BitBoard;

void bitboard_print(BitBoard board);

typedef enum {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN,
    NONE_TYPE,
} PieceType;

typedef enum {
    WHITE,
    BLACK,
} Color;

typedef enum {
    a8, b8, c8, d8, e8, f8, g8, h8, 
    a7, b7, c7, d7, e7, f7, g7, h7, 
    a6, b6, c6, d6, e6, f6, g6, h6, 
    a5, b5, c5, d5, e5, f5, g5, h5, 
    a4, b4, c4, d4, e4, f4, g4, h4, 
    a3, b3, c3, d3, e3, f3, g3, h3, 
    a2, b2, c2, d2, e2, f2, g2, h2, 
    a1, b1, c1, d1, e1, f1, g1, h1, 
} BoardPosition;


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

const extern BitBoard NOT_H_FILE;
const extern BitBoard NOT_A_FILE;
const extern BitBoard NOT_AB_FILE;
const extern BitBoard NOT_GH_FILE;

const extern BitBoard NOT_1_RANK;
const extern BitBoard NOT_8_RANK;
const extern BitBoard NOT_12_RANK;;
const extern BitBoard NOT_78_RANK;

const extern BitBoard FILE_2;
const extern BitBoard FILE_7;

BitBoard get_bit(BitBoard bitboard, int position);
BitBoard set_bit(BitBoard bitboard, int position);
BitBoard reset_bit(BitBoard bitboard, int position);

#endif
