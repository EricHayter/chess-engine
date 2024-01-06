#include "board.h"
#include <stdlib.h>
#include <stdio.h>

const Piece EMPTYSQUARE = {NONE_TYPE, NONE_COLOR};

int is_piece_equal(const Piece *piece1, const Piece *piece2) {
  // checks for equality of two pieces (irrespective of position on the board)
  return (piece1->pieceType == piece2->pieceType) &
         (piece1->color == piece2->color);
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
    for (int i = 0; i < 64; i++) {
        printf("%lu", (board >> i) & 1);
        if (i % 8 == 7)
            printf("\n");
    }
}


Board *move_piece(const Board *board, Piece *piece, uint8_t prev,
                  uint8_t next) {
  // crates a new bit board representation after the moving of a piece given
  // a current location and a new location. Assumes that a piece is present
  // in the current location.
  if ((prev >= 64) | (next >= 64))
    return NULL;

  Board *new_board = copy_board(board);
  uint64_t *bitboard;
  switch (piece->pieceType) {
  case KING: {
    if (piece->color == WHITE)
      bitboard = &new_board->wKing;
    else if (piece->color == BLACK)
      bitboard = &new_board->bKing;
    break;
  }
  case QUEEN: {
    if (piece->color == WHITE)
      bitboard = &new_board->wQueen;
    else if (piece->color == BLACK)
      bitboard = &new_board->bQueen;
    break;
  }
  case BISHOP: {
    if (piece->color == WHITE)
      bitboard = &new_board->wBishop;
    else if (piece->color == BLACK)
      bitboard = &new_board->bBishop;
    break;
  }
  case KNIGHT: {
    if (piece->color == WHITE)
      bitboard = &new_board->wKnight;
    else if (piece->color == BLACK)
      bitboard = &new_board->wKnight;
    break;
  }
  case ROOK: {
    if (piece->color == WHITE)
      bitboard = &new_board->wRook;
    else if (piece->color == BLACK)
      bitboard = &new_board->bRook;
    break;
  }
  case PAWN: {
    if (piece->color == WHITE)
      bitboard = &new_board->wPawn;
    else if (piece->color == BLACK)
      bitboard = &new_board->bPawn;
    break;
  }
  default:
    return NULL;
  }

  *bitboard &= ~(1 << prev); // remove the old 1 in the bitboard
  *bitboard |= 1 << next;    // add the new 1 into the bitboard

  return new_board;
}
