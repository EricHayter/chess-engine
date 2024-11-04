#include "board.h"
#include "attack_table.h"
#include <stdio.h>

int main() {
	init_attacks();
	BitBoard bb = EMPTY_BOARD;	
	bb = set_square(bb, C6);
//	board_print(QUEEN_ATTACKS[C4][0]);
//	board_print(QUEEN_ATTACKS[C4][1]);
	board_print(QUEEN_ATTACKS[C4][2]);
	board_print(QUEEN_ATTACKS[C4][3]);
//	board_print(QUEEN_ATTACKS[C4][4]);
//	board_print(QUEEN_ATTACKS[C4][5]);
//	board_print(QUEEN_ATTACKS[C4][6]);
//	board_print(QUEEN_ATTACKS[C4][7]);
}
