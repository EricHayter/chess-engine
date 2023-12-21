#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

enum class PieceType {
    Bishop,
    King,
    Knight,
    Pawn,
    Queen,
    Rook,
    None,
};

enum class Color {
    White,
    Black,
    None,
};

struct Piece {
    PieceType type;
    Color color;
};

struct Board {
    uint64_t Bbishop;
    uint64_t Bking;   
    uint64_t Bknight;
    uint64_t Bpawn;
    uint64_t Bqueen;
    uint64_t Brook;
    uint64_t Wbishop;
    uint64_t Wking;   
    uint64_t Wknight;
    uint64_t Wpawn;
    uint64_t Wqueen;
    uint64_t Wrook;
};

#endif
