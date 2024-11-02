#include "board.h"
#include <stdio.h>

int main() {
	BitBoard bb = 0x00;	
	bb = set_position(bb, C6);
	board_print(bb);
}
