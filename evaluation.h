#ifndef EVALUATION_H
#define EVALUATION_H

#include "board.h"
#include <stdint.h>

#define WHITE_WIN 9999 // TODO maybe choose a better value
#define BLACK_WIN 9999

double positionCoefficient(PieceType pt, Color clr, uint8_t pos);
double evaluate(Board* board);

#endif
