#include "board.h"
#include <stdlib.h>
#include <stdio.h>

// create an enum for each position on the board
// create a simmilar piece of code for the string representation

const Piece EMPTYSQUARE = {NONE_TYPE, NONE_COLOR};

int is_piece_equal(const Piece *piece1, const Piece *piece2) {
  // checks for equality of two pieces (irrespective of position on the board)
  return (piece1->pieceType == piece2->pieceType) &
         (piece1->color == piece2->color);
}

inline BitBoard get_bit(BitBoard bitboard, int position) {
    return bitboard & (1 << position);
}

inline BitBoard set_bit(BitBoard bitboard, int position) {
    return bitboard | (1 << position);
}

inline BitBoard reset_bit(BitBoard bitboard, int position) {
    return bitboard & ~(1 << position);
}

Board *copy_board(const Board *board) {
  // creates a copy of a given bitboard
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

void bitboard_print(BitBoard board) {
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            printf(" %d", (int) get_bit(board, square));
        } 

        printf("\n");
    }
}




