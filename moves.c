#include "board.h"
// #include "arraylist.h"


ArrayList validMoves(Board b, uint8_t pos) {
  std::vector<Coordinate> moves{};
  uint8_t NUM_ROWS = 8;
  uint8_t row = pos / NUM_ROWS;
  int col = std::get<1>(c);
  Piece piece {b[row][col]};

  switch (piece.type) {
    case PieceType::Bishop: {
      Piece p{};
      for (int i {1}; i < (8 - col) & i < (8 - col); i++) {
          p = {b[row][col + i]};
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row + i, col + i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i <= col & i <= row; i++) {
          p = b[row][col - i];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row - i, col - i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i < (8 - row) & i <= col; i++) {
          p = b[row + i][col - i];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row + i, col - i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; (i <= row) & (8 -col); i++) {
          p = b[row - i][col];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row - i, col + i});
          if (p.color == Color::None)
              break;
      }
      break;
    }

    case PieceType::King: {
      if ((row + 1 < 8) & (b[row+1][col].color != piece.color)) moves.push_back(Coordinate {row + 1, col});
      if ((row - 1 >= 0) & (b[row-1][col].color != piece.color)) moves.push_back(Coordinate {row - 1, col});
      if ((col + 1 < 8) & (b[row][col+1].color != piece.color)) moves.push_back(Coordinate {row, col + 1});
      if ((col - 1 >= 0) & (b[row][col-1].color != piece.color)) moves.push_back(Coordinate {row, col - 1});
      if ((row + 1 < 8 & col + 1 < 8) & (b[row+1][col+1].color != piece.color)) moves.push_back(Coordinate {row + 1, col + 1});
      if ((row - 1 >= 0 & col - 1 >= 0) & (b[row-1][col-1].color != piece.color)) moves.push_back(Coordinate {row - 1, col - 1});
      if ((row + 1 < 8 & col + 1 < 8) & (b[row+1][col+1].color != piece.color)) moves.push_back(Coordinate {row + 1, col + 1});
      if ((row - 1 >= 0 & col - 1 >= 0) & (b[row-1][col-1].color != piece.color)) moves.push_back(Coordinate {row - 1, col - 1});
      // castle is going to be annoying
      // just don't include it I guess for now
      break;
    }
    case PieceType::Knight: {
    // fix the indexes in the columns
      if ((row + 2 < 8 & col + 1 < 8) &
              (b[row+2][col+1].color != piece.color)) moves.push_back(Coordinate {row + 2, col + 1});
      if ((row + 2 < 8 & col - 1 >= 0) &
              (b[row+2][col-1].color != piece.color)) moves.push_back(Coordinate {row + 2, col - 1});
      if ((row - 2 >= 0 & col + 1 < 8) &
              (b[row-2][col+1].color != piece.color)) moves.push_back(Coordinate {row - 2, col + 1});
      if ((row - 2 >= 0 & col - 1 >= 0) &
              (b[row-2][col-1].color != piece.color)) moves.push_back(Coordinate {row - 2, col - 1});
      if ((row + 1 < 8 & col + 2 < 8) &
              (b[row+1][col+2].color != piece.color)) moves.push_back(Coordinate {row + 1, col + 2});
      if ((row - 1 >= 0 & col + 2 < 8) &
              (b[row-1][col+2].color != piece.color)) moves.push_back(Coordinate {row - 1, col + 2});
      if ((row + 1 < 8 & col - 2 >= 0) &
              (b[row+1][col-2].color != piece.color)) moves.push_back(Coordinate {row + 1, col - 2});
      if ((row - 1 >= 0 & col - 2 >= 0) &
              (b[row-1][col-2].color != piece.color)) moves.push_back(Coordinate {row - 1, col - 2});

      break;
    }
    case PieceType::Pawn: {
      // we won't implement en pessant for the moment as it's a bit of an edge case move (won't make or break in most cases)
      if ((piece.type == Color::White) & (row + 1 < 8) & (b[row+1][col].type == PieceType::None)) {
        if (row == 1 & b[row+2][col].type == PieceType::None) {
              moves.push_back(Coordinate {row, col + 2}); 
        }
       }
      

      if (piece.type == Collor::Black) {
      
      }
      break;
    }
    case PieceType::Queen: {
      Piece p{};
      for (int i {1}; i < (8 - col); i++) { // this is fishy
          p = b[row][col + i];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row, col + i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i <= col; i++) {
          p = b[row][col - i];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row, col - i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i < (8 - row); i++) {
          p = b[row + i][col];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row + i, col});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i <= row; i++) {
          p = b[row - i][col];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row - i, col});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i < (8 - col) & i < (8 - col); i++) {
          p = {b[row][col + i]};
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row + i, col + i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i <= col & i <= row; i++) {
          p = b[row][col - i];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row - i, col - i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; i < (8 - row) & i <= col; i++) {
          p = b[row + i][col - i];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row + i, col - i});
          if (p.color == Color::None)
              break;
      }
      for (int i {1}; (i <= row) & (8 -col); i++) {
          p = b[row - i][col];
          if (p.color == piece.color)
              break;
          moves.push_back(Coordinate {row - i, col + i});
          if (p.color == Color::None)
              break;
      }

      break;
                           }

    case PieceType::Rook: {
                              Piece p{};
                              for (int i {1}; i < (8 - col); i++) { // this is fishy
                                  p = b[row][col + i];
                                  if (p.color == piece.color)
                                      break;
                                  moves.push_back(Coordinate {row, col + i});
                                  if (p.color == Color::None)
                                      break;
                              }
                              for (int i {1}; i <= col; i++) {
                                  p = b[row][col - i];
                                  if (p.color == piece.color)
                                      break;
                                  moves.push_back(Coordinate {row, col - i});
                                  if (p.color == Color::None)
                                      break;
                              }
                              for (int i {1}; i < (8 - row); i++) {
                                  p = b[row + i][col];
                                  if (p.color == piece.color)
                                      break;
                                  moves.push_back(Coordinate {row + i, col});
                                  if (p.color == Color::None)
                                      break;
                              }
                              for (int i {1}; i <= row; i++) {
                                  p = b[row - i][col];
                                  if (p.color == piece.color)
                                      break;
                                  moves.push_back(Coordinate {row - i, col});
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
