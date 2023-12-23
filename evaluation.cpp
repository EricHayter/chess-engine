#include "evaluation.h"

#include <cstdint>
#include <limits>

#include "board.h"

double positionCoefficient(const PieceType &pt, const uint8_t pos) {
  // use this to improve the evaluation function later
  // figure out later what is playing optimally
  // pieces are more useful at certain squares
  return 1.0;
}

double evaluate(const Board &board) {
  // in favor of white (> 0)
  // in favor of black (< 0)
  // equal (= 0)
  double evaluation{0.0};

  // if the kings aren't on the board you lose -/+ infinity
  if (board.Bking == 0) return std::numeric_limits<double>::max();
  if (board.Wking == 0) return std::numeric_limits<double>::min();

  for (uint8_t i{0}; i < sizeof(uint64_t); i++) {
    // pawns
    if ((board.Wpawn << i) & 1)
      evaluation += positionCoefficient(PieceType::Pawn, i);
    if ((board.Bpawn << i) & 1)
      evaluation -= positionCoefficient(PieceType::Pawn, i);

    // knights
    if ((board.Wknight << i) & 1)
      evaluation += 3 * positionCoefficient(PieceType::Knight, i);
    if ((board.Bknight << i) & 1)
      evaluation += 3 * positionCoefficient(PieceType::Knight, i);

    // bishops TODO is it worth to give 4 rating (???)
    if ((board.Wbishop << i) & 1)
      evaluation += 3 * positionCoefficient(PieceType::Bishop, i);
    if ((board.Bbishop << i) & 1)
      evaluation -= 3 * positionCoefficient(PieceType::Bishop, i);

    // rooks
    if ((board.Wrook << i) & 1)
      evaluation += 5 * positionCoefficient(PieceType::Rook, i);
    if ((board.Brook << i) & 1)
      evaluation -= 5 * positionCoefficient(PieceType::Rook, i);

    // queens
    if ((board.Wqueen << i) & 1)
      evaluation += 9 * positionCoefficient(PieceType::Queen, i);
    if ((board.Bqueen << i) & 1)
      evaluation -= 9 * positionCoefficient(PieceType::Queen, i);
  }

  return evaluation;
}
