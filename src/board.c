#include "board.h"

#include <stdio.h>

void board_print(BitBoard bb)
{
	for (int i = 0; i < 8; i++) {
		printf("%d  ", 8 - i);
		for (int j = 0; j < 8; j++) {
			if (bb << (i * 8 + j) & 1)
				printf("1");
			else
				printf("0");
		}
		printf("\n");
	}
	printf("   ABCDEFGH");
	printf("   Bitboard: %llu", bb);
}
