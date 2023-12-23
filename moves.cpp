#include <vector>
#include "board.h"

// just return the valid moves instead of checking
std::vector<Coordinate> validMoves(const Board &b, int row, int col) {
  std::vector<Coordinate> moves{};
  // pass in the color of the piece somehow
  Piece piece {b[row][col]};
  switch (piece.type) {
    case PieceType::Bishop: {
      break;
    }
    case PieceType::King: {
      break;
    }
    case PieceType::Knight: {
      break;
    }
    case PieceType::Pawn: {
      break;
    }
    case PieceType::Queen: {
      break;
    }
    case PieceType::Rook: {
      for (int i {1}; i < (8 - col); i++) { // this is fishy
          Piece p {b[row][col + i]};
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row, col + i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i < col; i++) {
          Piece p {b[row][col - i]};
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row, col - i});
          if (p.color == Color::None)
              break;
      }
      break;
    }
    case PieceType::None:
      break;
  }

  return moves;
}
