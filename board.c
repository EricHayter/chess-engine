#include "board.h"
#include <stdio.h>
#include <stdlib.h>

const BitBoard NOT_H_FILE = (BitBoard) 9187201950435737471ull;
const BitBoard NOT_A_FILE = (BitBoard) 18374403900871474942ull;
const BitBoard NOT_AB_FILE = (BitBoard) 18229723555195321596ull; 
const BitBoard NOT_GH_FILE = (BitBoard) 4557430888798830399ull; 

const BitBoard NOT_1_RANK = (BitBoard) 72057594037927935ull;
const BitBoard NOT_8_RANK = (BitBoard) 18446744073709551360ull;
const BitBoard NOT_12_RANK = (BitBoard) 281474976710655ull;
const BitBoard NOT_78_RANK = (BitBoard) 18446744073709486080ull;

const BitBoard FILE_2 = 71776119061217280ull; 
const BitBoard FILE_7 = 65280ull; 

BitBoard get_bit(BitBoard bitboard, int position) {
    return bitboard & (1ull << position);
}

BitBoard set_bit(BitBoard bitboard, int position) {
    return bitboard | (1ull << position);
}

BitBoard reset_bit(BitBoard bitboard, int position) {
    return bitboard & ~(1ull << position);
}

Board *copy_board(const Board *board) {
  // creates a copy of a given boardstate
  Board *new_board = malloc(sizeof(Board *));
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


BitBoard get_occupied(Board* board)
{
    return board->wKing |
        board->wQueen |
        board->wBishop |
        board->wKnight |
        board->wRook |
        board->wPawn |
        board->bKing |
        board->bQueen |
        board->bBishop |
        board->bKnight |
        board->bRook |
        board->bPawn;
}
    

void bitboard_print(BitBoard board)
{
    printf("\n\n");
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
            printf("  %d ", 8 - (i / 8));
        printf(" %llu", (board >> i) & 1);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n     a b c d e f g h\n\n");
    printf("  Bitboard: %llu\n", board);
}


