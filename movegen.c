#include "board.h"
#include "movelist.h"
#include "moves.h"

// adds all moves to the movelist.
void add_moves(MoveList *movelist, Board *board, BoardPosition origin)
{

    PieceType type = get_piece_type(board, origin);
    BitBoard enemy = get_enemy_squares(board);
    BitBoard occupied = get_occupied_squares(board);
    BitBoard moves;

    switch (type) {
    case KING:
       moves = king_moves(board, origin); 
       break;
    case QUEEN:
       moves = queen_moves(board, origin);
       break;
    case BISHOP:
       moves = bishop_moves(board, origin);
       break;
    case KNIGHT:
       moves = knight_moves(board, origin);
       break;
    case ROOK:
       moves = rook_moves(board, origin);
       break;
    case PAWN: // we don't handle the pawn moves here
       moves = pawn_pushes(board, origin) | pawn_attacks(board, origin);
       break;
    }

    BoardPosition attack_square;
    while (moves) {
        attack_square = LSB(moves); 
        moves = reset_bit(moves, attack_square);

        if (set_bit(0ull, attack_square) & enemy) {
            movelist_push(movelist, create_move(origin, attack_square, CAPTURE));
        } else if (set_bit(0ull, attack_square) & ~occupied) {
            movelist_push(movelist, create_move(origin, attack_square, QUIET_MOVE));
        }
    }

}

