#ifndef EVALUATION_H
#define EVALUATION_H

#include <stdint.h>
#include "board.h"

double positionCoefficient(enum PieceType pt, enum Color clr, uint8_t pos);
double evaluate(struct Board* board);

#endif
