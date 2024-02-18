#ifndef MOVELIST_H
#define MOVELIST_H

#include "moves.h"
#include <stddef.h>

typedef struct {
    size_t capacity;
    size_t num_moves; 
    Move **moves;
} MoveList;

MoveList *movelist_create();
void movelist_destroy(MoveList *movelist);
size_t movelist_size(MoveList* movelist);
void movelist_push(MoveList *movelist, Move *move);
Move* movelist_get(MoveList* movelist, size_t idx);

#endif
