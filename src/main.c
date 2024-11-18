#include "board.h"
#include "attack_table.h"
#include "move_gen.h"
#include <stdio.h>

int main() {
	init_attacks();
	BitBoard bb = EMPTY_BOARD;	
	bb = set_square(bb, C6);
	board_print(QUEEN_ATTACKS[C4][2]);
	board_print(QUEEN_ATTACKS[C4][3]);

	printf("%d\n", bitscan_backward(set_square(0x00, H1)));
}
