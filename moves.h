#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdint>

std::vector<uint8_t>
validMoves (const Board &b, const Piece &piece, int pos);

#endif
