#include "board.h"
#include <cstdint>
#include <vector>

// bool isValidMove(const Board& b, const PieceType& pt, uint8_t cur, uint8_t next)
// {
//     // we won't worry about moving into checks as this will be evaluated by
//     // the evaluation function itself (i.e. only move into check if game over)
// 
//     // positions = 8 * row # + col #
//     if (cur == next)
//         return false;
//     
//      switch (pt) {
//         case PieceType::Bishop:
//            break; 
//         case PieceType::King:
//            break;
//         case PieceType::Knight:
//            break;
//         case PieceType::Pawn:
//            break;
//         case PieceType::Queen:
//            break;
//         case PieceType::Rook:
//            break;
//     }
// 
// 
//     return true;
// }

// just return the valid moves instead of checking
std::vector<uint8_t> validMoves(const Board& b, const Piece& piece, int pos) {
    std::vector<uint8_t> moves {}; 
    // pass in the color of the piece somehow

    switch (piece.type) {
    case PieceType::Bishop: {
                                break; 
                            }
    case PieceType::King: {
                              break;
                          }
    case PieceType::Knight:{
                               break;
                           }
    case PieceType::Pawn: {
                              break;
                          }
    case PieceType::Queen: {
                               break;
                           }
    case PieceType::Rook: {
                              int x {pos / 8}; // col
                              int y {pos % 8}; // row
                              break;
                          }
    case PieceType::None:
                          break;
    }

    return moves;
}
