#ifndef MOVES_H
#define MOVES_H

#include "board.h"
#include "arraylist.h"
#include <stdint.h>

Piece* isOccupied(Board* board, uint8_t pos);
ArrayList* bishopMoves(Board* board, uint8_t pos);
ArrayList* kingMoves(Board* board, uint8_t pos);
ArrayList* knightMoves(Board* board, uint8_t pos);
ArrayList* pawnMoves(Board* board, uint8_t pos);
ArrayList* queenMoves(Board* board, uint8_t pos);
ArrayList* rookMoves(Board* board, uint8_t pos);

#endif
