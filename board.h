#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <array>
#include <tuple>

enum class PieceType {
    Bishop,
    King,
    Knight,
    Pawn,
    Queen,
    Rook,
    None, // empty slots
};

enum class Color {
    White,
    Black,
    None, // empty slots
};

struct Piece {
    PieceType type;
    Color color;
};

using Board = std::array<std::array<Piece, 8> ,8>; // type alias for boards
using Coordinate = std::tuple<int, int>;

#endif
