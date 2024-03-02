#include "evaluation.h"
#include "board.h"
#include <stdio.h>

#include "moves.h"

double positionCoefficient(PieceType pt, Color clr, uint8_t pos)
{
    // use this to improve the evaluation function later
    // figure out later what is playing optimally
    // pieces are more useful at certain squares
    return 1.0;
}

double evaluate(Board *board)
{
    // in favor of white (> 0)
    // in favor of black (< 0)
    // equal (= 0)
    double evaluation = 0.0;

    // if the kings aren't on the board you lose -/+ infinity
    if (board->bKing == 0)
        return WHITE_WIN;
    if (board->wKing == 0)
        return BLACK_WIN;

    for (uint8_t i = 0; i < sizeof(uint64_t); i++)
    {
        // pawns
        if ((board->wPawn << i) & 1)
            evaluation += positionCoefficient(PAWN, WHITE, i);
        if ((board->bPawn << i) & 1)
            evaluation -= positionCoefficient(PAWN, BLACK, i);

        // knights
        if ((board->wKnight << i) & 1)
            evaluation += 3 * positionCoefficient(KNIGHT, WHITE, i);
        if ((board->bKnight << i) & 1)
            evaluation += 3 * positionCoefficient(KNIGHT, BLACK, i);

        // bishops TODO is it worth to give 4 rating (???)
        if ((board->wBishop << i) & 1)
            evaluation += 3 * positionCoefficient(BISHOP, WHITE, i);
        if ((board->bBishop << i) & 1)
            evaluation -= 3 * positionCoefficient(BISHOP, BLACK, i);

        // rooks
        if ((board->wRook << i) & 1)
            evaluation += 5 * positionCoefficient(ROOK, WHITE, i);
        if ((board->bRook << i) & 1)
            evaluation -= 5 * positionCoefficient(ROOK, BLACK, i);

        // queens
        if ((board->wQueen << i) & 1)
            evaluation += 9 * positionCoefficient(QUEEN, WHITE, i);
        if ((board->bQueen << i) & 1)
            evaluation -= 9 * positionCoefficient(QUEEN, BLACK, i);
    }

    return evaluation;
}

int main() 
{
    Board *board = init_board();
    board->turn = WHITE;
    board->wPawn = set_bit(0ull, b3);
    bitboard_print(pawn_pushes(board, b2));
    return 0;
}
