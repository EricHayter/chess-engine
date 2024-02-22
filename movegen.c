#include "board.h"
#include "movelist.h"
#include "moves.h"

// adds all "basic" moves to the movelist. Loosely using basic as a way of saying
// non-pawn moves and non castling.
void add_basic_moves(MoveList *movelist, Board *board, BoardPosition origin)
{

    PieceType type = get_piece_type(board, origin);
    BitBoard enemy = get_enemy_squares(board);
    BitBoard occupied = get_occupied(board);
    BitBoard moves;

    switch (type) {
    case KING:
       moves = king_moves(origin); 
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
       return;
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

void add_pawn_moves(MoveList *movelist, Board *board, BoardPosition origin)
{
    BitBoard moves = pawn_attacks(origin, board->turn); 
    BitBoard enemy = get_enemy_squares(board);

    BoardPosition attack_square;
    while (moves) {
        attack_square = LSB(moves); 
        moves = reset_bit(moves, attack_square);

        if (set_bit(0ull, attack_square) & enemy) {
            movelist_push(movelist, create_move(origin, attack_square, CAPTURE));
        }
    }
}
