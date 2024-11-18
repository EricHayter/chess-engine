#pragma once

#include <stdlib.h>
#include "move.h"

#define DEFAULT_CAPACITY 5
#define GROWTH_RATE 2

typedef struct MoveList_t {
	Move *moves;
	int len;
	int capacity;
} MoveList;

MoveList *init_movelist();
void free_movelist(MoveList *movelist);
void add_move(MoveList *movelist, Move move);
