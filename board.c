#include "board.h"
#include <stdio.h>
#include <stdlib.h>

const U64 NOT_H_FILE = (U64) 9187201950435737471ull;
const U64 NOT_A_FILE = (U64) 18374403900871474942ull;
const U64 NOT_AB_FILE = (U64) 18229723555195321596ull; 
const U64 NOT_GH_FILE = (U64) 4557430888798830399ull; 

const U64 NOT_1_RANK = (U64) 72057594037927935ull;
const U64 NOT_8_RANK = (U64) 18446744073709551360ull;
const U64 NOT_12_RANK = (U64) 281474976710655ull;
const U64 NOT_78_RANK = (U64) 18446744073709486080ull;

const U64 RANK_2 = 71776119061217280ull; 
const U64 RANK_7 = 65280ull; 

U64 get_bit(U64 U64, int position) {
    return U64 & (1ull << position);
}

U64 set_bit(U64 U64, int position) {
    return U64 | (1ull << position);
}

U64 reset_bit(U64 U64, int position) {
    return U64 & ~(1ull << position);
}

Board *copy_board(const Board *board) 
{
    // creates a copy of a given boardstate
    Board *new_board = malloc(sizeof(Board));
    new_board->wKing = board->wKing;
    new_board->wQueen = board->wQueen;
    new_board->wBishop = board->wBishop;
    new_board->wKnight = board->wKnight;
    new_board->wRook = board->wRook;
    new_board->wPawn = board->wPawn;
    new_board->wKing = board->wKing;
    new_board->wQueen = board->wQueen;
    new_board->wBishop = board->wBishop;
    new_board->wKnight = board->wKnight;
    new_board->wRook = board->wRook;
    new_board->wPawn = board->wPawn;
    return new_board;
}

Board *init_board()
{
    Board *board = malloc(sizeof(Board));
    return board;
}


/*
   "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
   "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
   "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
   "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
   "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
   "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
   "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
   "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
   */


U64 get_occupied_squares(Board* board)
{
    return get_friendly_squares(board) | get_enemy_squares(board);
}

U64 get_vacant_squares(Board* board)
{
    return ~get_occupied_squares(board);
}


void bitboard_print(U64 bb)
{
    printf("\n\n");
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
            printf("  %d ", 8 - (i / 8));
        printf(" %llu", (bb >> i) & 1);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n     a b c d e f g h\n\n");
    printf("  U64: %llu\n", bb);
}


U64 get_friendly_squares(Board* board)
{
    switch (board->turn)
    {
        case WHITE:
            return board->wKing |
                board->wQueen |
                board->wBishop |
                board->wKnight |
                board->wRook |
                board->wPawn;
        case BLACK:
            return board->bKing |
                board->bQueen |
                board->bBishop |
                board->bKnight |
                board->bRook |
                board->bPawn;
    }
}

U64 get_enemy_squares(Board* board)
{
    switch (board->turn)
    {
        case WHITE:
            return board->bKing |
                board->bQueen |
                board->bBishop |
                board->bKnight |
                board->bRook |
                board->bPawn;
        case BLACK:
            return board->wKing |
                board->wQueen |
                board->wBishop |
                board->wKnight |
                board->wRook |
                board->wPawn;
    }
}

PieceType get_piece_type(Board* board, BoardPosition position)
{
    if (1 << position & (board->wKing | board->bKing)) return KING;
    if (1 << position & (board->wQueen | board->bQueen)) return QUEEN;
    if (1 << position & (board->wBishop | board->bBishop)) return BISHOP;
    if (1 << position & (board->wKnight | board->bKnight)) return KNIGHT;
    if (1 << position & (board->wRook | board->bRook)) return ROOK;
    else return PAWN;
}
