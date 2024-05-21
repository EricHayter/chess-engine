#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdbool.h>

typedef unsigned long long U64;

void bitboard_print(U64 bb);

typedef enum {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
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
    Color turn;
    BoardPosition en_passant_square; // starting position of pawn that made
                                     // en passant move (o if no move)
    bool castlingRights[4];
    U64 doublePawnMove; // location of pawn that moved 2 squares
    U64 wKing;
    U64 wQueen;
    U64 wBishop;
    U64 wKnight;
    U64 wRook;
    U64 wPawn;
    U64 bKing;
    U64 bQueen;
    U64 bBishop;
    U64 bKnight;
    U64 bRook;
    U64 bPawn;
} Board;

typedef enum {
    wKingSide,
    wQueenSide,
    bKingSide,
    bQueenSide,
} CastlingRight;

Board *init_board();

typedef struct {
    PieceType pieceType;
    Color color;
} Piece;

const extern U64 NOT_H_FILE;
const extern U64 NOT_A_FILE;
const extern U64 NOT_AB_FILE;
const extern U64 NOT_GH_FILE;

const extern U64 NOT_1_RANK;
const extern U64 NOT_8_RANK;
const extern U64 NOT_12_RANK;;
const extern U64 NOT_78_RANK;

const extern U64 RANK_2;
const extern U64 RANK_7;

U64 get_bit(U64 U64, int position);
U64 set_bit(U64 U64, int position);
U64 reset_bit(U64 U64, int position);

U64 get_occupied_squares(Board* board);
U64 get_vacant_squares(Board* board);
U64 get_friendly_squares(Board* board);
U64 get_enemy_squares(Board* board);
PieceType get_piece_type(Board* board, BoardPosition position);

#endif
