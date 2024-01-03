#ifndef MOVES_H
#define MOVES_H

#include "board.h"
#include "arraylist.h"
#include <stdint.h>

Piece* isOccupied(const Board* board, uint8_t pos);
ArrayList* bishopMoves(const Board* board, uint8_t pos);
ArrayList* kingMoves(const Board* board, uint8_t pos);
ArrayList* knightMoves(const Board* board, uint8_t pos);
ArrayList* pawnMoves(const Board* board, uint8_t pos);
ArrayList* queenMoves(const Board* board, uint8_t pos);
ArrayList* rookMoves(const Board* board, uint8_t pos);

#endif
