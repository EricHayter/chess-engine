#ifndef EVALUATION_H
#define EVALUATION_H

#include "board.h"

double positionCoefficient(const PieceType& pt, const uint8_t pos);
double evaluate(const Board& board);

#endif
