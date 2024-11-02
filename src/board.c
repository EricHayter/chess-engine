#include "board.h"
#include <stdio.h>

BitBoard set_position(BitBoard bb, Position pos)
{
	return bb | 1 << pos;
}

void board_print(BitBoard bb)
{
	for (int i = 0; i < 8; i++) {
		printf("%d  ", 8 - i);
		for (int j = 0; j < 8; j++) {
			if (bb & 1 << (i * 8 + j))
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n   A B C D E F G H\n");
	printf("   Bitboard: %llu\n", bb);
}
