#include "board.h"
#include "movelist.h"
#include "moves.h"

// adds all moves to the movelist.
void add_moves(MoveList *movelist, Board *board, BoardPosition origin)
{
    PieceType type = get_piece_type(board, origin);
    BitBoard enemy = get_enemy_squares(board);
    BoardPosition move_dest;
    BitBoard moves;

    switch (type) {
        case KING:
            // handle our special cases first (i.e. castling leave the rest for generic)
            moves = castling_moves(board);
            if (set_bit(0ull, c1) & moves)
                movelist_push(movelist, create_move(origin, c1, KING_CASTLE));
            if (set_bit(0ull, g1) & moves)
                movelist_push(movelist, create_move(origin, g1, QUEEN_CASTLE));
            if (set_bit(0ull, c8) & moves)
                movelist_push(movelist, create_move(origin, c8, KING_CASTLE));
            if (set_bit(0ull, g8) & moves)
                movelist_push(movelist, create_move(origin, g8, QUEEN_CASTLE));
            moves = king_moves(board, origin);
            break;
        case PAWN:
            moves = pawn_pushes(board, origin) | pawn_attacks(board, origin);
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
    }

    while (moves) {
        move_dest = LSB(moves); 
        moves = reset_bit(moves, move_dest);

        if (set_bit(0ull, move_dest) & enemy) {
            // pawn cases
            if (type == PAWN) {

            }
            movelist_push(movelist, create_move(origin, move_dest, CAPTURE));
        } else {
            movelist_push(movelist, create_move(origin, move_dest, QUIET_MOVE));
        }
    }
}

