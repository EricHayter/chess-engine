#include "board.h"
#include "moves.h"
#include <stdio.h>

int main() {
	init_distances();
	init_king_attacks();
	init_rook_attacks();
	BitBoard bb = EMPTY_BOARD;	
	bb = set_position(bb, C6);
	board_print(ROOK_ATTACKS[A1]);
}
