#include "board.h"
#include "moves.h"
#include <stdio.h>

int main() {
	init_attacks();
	BitBoard bb = EMPTY_BOARD;	
	bb = set_position(bb, C6);
	board_print(BISHOP_ATTACKS[C4]);
}
