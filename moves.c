#include "moves.h"
#include "arraylist.h"
#include "board.h"

ArrayList *validMoves(Board *board) {
  // generate a list of possible moves in a given position
  ArrayList *moves = arraylist_create();
  for (uint8_t pos = 0; pos < 64; pos++) {
    Piece *occupant = isOccupied(board, pos);
    if (is_piece_equal(occupant, &EMPTY))
      continue;

    switch (occupant->pieceType) {
    case BISHOP: {
      ArrayList *bishop_moves = bishopMoves(board, pos);
      for (uint32_t i = 0; i < bishop_moves->size; i++)
        push(moves, get(bishop_moves, i));
      destroy_list(bishop_moves);
      break;
    }
    case KING: {
    }
    case KNIGHT: {
    }
    case PAWN: {
    }
    case QUEEN: {
    }
    case ROOK: {
    }
    default:
      break;
    }

  case PieceType::King: {
    if ((row + 1 < 8) & (b[row + 1][col].color != piece.color))
      moves.push_back(Coordinate{row + 1, col});
    if ((row - 1 >= 0) & (b[row - 1][col].color != piece.color))
      moves.push_back(Coordinate{row - 1, col});
    if ((col + 1 < 8) & (b[row][col + 1].color != piece.color))
      moves.push_back(Coordinate{row, col + 1});
    if ((col - 1 >= 0) & (b[row][col - 1].color != piece.color))
      moves.push_back(Coordinate{row, col - 1});
    if ((row + 1 < 8 & col + 1 < 8) &
        (b[row + 1][col + 1].color != piece.color))
      moves.push_back(Coordinate{row + 1, col + 1});
    if ((row - 1 >= 0 & col - 1 >= 0) &
        (b[row - 1][col - 1].color != piece.color))
      moves.push_back(Coordinate{row - 1, col - 1});
    if ((row + 1 < 8 & col + 1 < 8) &
        (b[row + 1][col + 1].color != piece.color))
      moves.push_back(Coordinate{row + 1, col + 1});
    if ((row - 1 >= 0 & col - 1 >= 0) &
        (b[row - 1][col - 1].color != piece.color))
      moves.push_back(Coordinate{row - 1, col - 1});
    // castle is going to be annoying
    // just don't include it I guess for now
    break;
  }
  case PieceType::Knight: {
    // fix the indexes in the columns
    if ((row + 2 < 8 & col + 1 < 8) &
        (b[row + 2][col + 1].color != piece.color))
      moves.push_back(Coordinate{row + 2, col + 1});
    if ((row + 2 < 8 & col - 1 >= 0) &
        (b[row + 2][col - 1].color != piece.color))
      moves.push_back(Coordinate{row + 2, col - 1});
    if ((row - 2 >= 0 & col + 1 < 8) &
        (b[row - 2][col + 1].color != piece.color))
      moves.push_back(Coordinate{row - 2, col + 1});
    if ((row - 2 >= 0 & col - 1 >= 0) &
        (b[row - 2][col - 1].color != piece.color))
      moves.push_back(Coordinate{row - 2, col - 1});
    if ((row + 1 < 8 & col + 2 < 8) &
        (b[row + 1][col + 2].color != piece.color))
      moves.push_back(Coordinate{row + 1, col + 2});
    if ((row - 1 >= 0 & col + 2 < 8) &
        (b[row - 1][col + 2].color != piece.color))
      moves.push_back(Coordinate{row - 1, col + 2});
    if ((row + 1 < 8 & col - 2 >= 0) &
        (b[row + 1][col - 2].color != piece.color))
      moves.push_back(Coordinate{row + 1, col - 2});
    if ((row - 1 >= 0 & col - 2 >= 0) &
        (b[row - 1][col - 2].color != piece.color))
      moves.push_back(Coordinate{row - 1, col - 2});

    break;
  }
  case PieceType::Pawn: {
    // we won't implement en pessant for the moment as it's a bit of an edge
    // case move (won't make or break in most cases)
    if ((piece.type == Color::White) & (row + 1 < 8) &
        (b[row + 1][col].type == PieceType::None)) {
      if (row == 1 & b[row + 2][col].type == PieceType::None) {
        moves.push_back(Coordinate{row, col + 2});
      }
    }

    if (piece.type == Collor::Black) {
    }
    break;
  }
  case PieceType::Queen: {
    Piece p{};
    for (int i{1}; i < (8 - col); i++) { // this is fishy
      p = b[row][col + i];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row, col + i});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i <= col; i++) {
      p = b[row][col - i];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row, col - i});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i < (8 - row); i++) {
      p = b[row + i][col];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row + i, col});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i <= row; i++) {
      p = b[row - i][col];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row - i, col});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i < (8 - col) & i < (8 - col); i++) {
      p = {b[row][col + i]};
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row + i, col + i});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i <= col & i <= row; i++) {
      p = b[row][col - i];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row - i, col - i});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i < (8 - row) & i <= col; i++) {
      p = b[row + i][col - i];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row + i, col - i});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; (i <= row) & (8 - col); i++) {
      p = b[row - i][col];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row - i, col + i});
      if (p.color == Color::None)
        break;
    }

    break;
  }

  case PieceType::Rook: {
    Piece p{};
    for (int i{1}; i < (8 - col); i++) { // this is fishy
      p = b[row][col + i];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row, col + i});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i <= col; i++) {
      p = b[row][col - i];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row, col - i});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i < (8 - row); i++) {
      p = b[row + i][col];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row + i, col});
      if (p.color == Color::None)
        break;
    }
    for (int i{1}; i <= row; i++) {
      p = b[row - i][col];
      if (p.color == piece.color)
        break;
      moves.push_back(Coordinate{row - i, col});
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

Piece *isOccupied(const Board *board, uint8_t pos) {
  if ((board->bBishop >> pos) && 1)
    return &((Piece){BISHOP, BLACK});
  if ((board->wBishop >> pos) && 1)
    return &((Piece){BISHOP, WHITE});

  if ((board->bKing >> pos) && 1)
    return &((Piece){KING, BLACK});
  if ((board->wKing >> pos) && 1)
    return &((Piece){KING, WHITE});

  if ((board->bKnight >> pos) && 1)
    return &((Piece){KNIGHT, BLACK});
  if ((board->wKnight >> pos) && 1)
    return &((Piece){KNIGHT, WHITE});

  if ((board->bPawn >> pos) && 1)
    return &((Piece){PAWN, BLACK});
  if ((board->wPawn >> pos) && 1)
    return &((Piece){PAWN, WHITE});

  if ((board->bQueen >> pos) && 1)
    return &((Piece){QUEEN, BLACK});
  if ((board->wQueen >> pos) && 1)
    return &((Piece){QUEEN, WHITE});

  if ((board->bRook >> pos) && 1)
    return &((Piece){ROOK, BLACK});
  if ((board->wRook >> pos) && 1)
    return &((Piece){ROOK, WHITE});

  return &EMPTY; // empty spot on board
}

ArrayList *bishopMoves(const Board *board, Color clr, uint8_t current_pos) {
  Piece *piece;
  int location;
  for (int i = 0; current_pos + i + i*ROW < 64; i++) { // fix this not very simple
    location = current_pos + i + i * ROW;
    piece = isOccupied(board, current_pos);
    if (piece->color == clr)
      break;

    // add new bitboard
    if (piece->color == clr)
      break;
  }
  for (int i{1}; i <= col & i <= row; i++) {
    p = b[row][col - i];
    if (p.color == piece.color)
      break;
    moves.push_back(Coordinate{row - i, col - i});
    if (p.color == Color::None)
      break;
  }
  for (int i{1}; i < (8 - row) & i <= col; i++) {
    p = b[row + i][col - i];
    if (p.color == piece.color)
      break;
    moves.push_back(Coordinate{row + i, col - i});
    if (p.color == Color::None)
      break;
  }
  for (int i{1}; (i <= row) & (8 - col); i++) {
    p = b[row - i][col];
    if (p.color == piece.color)
      break;
    moves.push_back(Coordinate{row - i, col + i});
    if (p.color == Color::None)
      break;
  }
  break;
}
