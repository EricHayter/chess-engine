#include "board.h"
#include "move_list.h"
#include "assert.h"

int bitscan_forward(BitBoard bb)
{
	// we won't allow empty bitboards
	assert(bb);
	
	int idx = 0;
	while (!(bb & 1)) {
		bb >>= 1;
		idx++;
	}
	return idx;
}

int bitscan_backward(BitBoard bb)
{
	assert(bb);

	int idx = 63;
	while (!(bb & 1ull << 63)) {
		bb <<= 1;	
		idx--;
	}
	return idx;
}

void get_knight_moves(MoveList *movelist, Game *game)
{
	BitBoard knight_positions = game->piece_occupancy[game->to_move * NUM_PIECE_TYPES + KNIGHT]; 
	while (knight_positions != EMPTY_BOARD) {
		Move move;	
		Square start;
	}

}
