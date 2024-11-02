#include "board.h"
#include <stdio.h>

int main() {
	init_distances();
	BitBoard bb = 0ull;	
	bb = set_position(bb, C6);
	board_print(bb);
}
