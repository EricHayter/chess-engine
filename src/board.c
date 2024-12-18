#include "board.h"
#include <stdio.h>

int distances_init = 0;
int DISTANCES[64][64];

int abs(int x) { return x >= 0 ? x : -x; }
int max(int x, int y) { return x >= y ? x : y; };
int row(Square sq) { return 8 - sq / 8; };
int col(Square sq) { return sq % 8 + 1; };
void init_distances()
{
	distances_init = 1;
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			DISTANCES[i][j] = max(abs(row(i) - row(j)), abs(col(i) - col(j)));
		}	
	}
}



BitBoard set_square(BitBoard bb, Square sq)
{
	return bb | 1ull << sq;
}

void board_print(BitBoard bb)
{
	for (int i = 0; i < 8; i++) {
		printf("%d  ", 8 - i);
		for (int j = 0; j < 8; j++) {
			if (bb & 1ull << (i * 8 + j))
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n   A B C D E F G H\n");
	printf("   Bitboard: %llu\n", bb);
}
