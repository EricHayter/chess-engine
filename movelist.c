/*
 * Simple structure for dynamic storage of moves. Going to use this instead
 * of the arraylist implementation since casting to void pointers is going
 * to make me cry.
 */

#include "moves.h"
#include <stdlib.h>

#define DEFAULT_SIZE 10 // default size for a movelist
#define GROWTH_RATE 2   // double the size each time it fills

typedef struct {
    size_t capacity;
    size_t num_moves; 
    Move **moves;
} MoveList;

MoveList *movelist_create()
{
    MoveList *movelist = malloc(sizeof(MoveList)); 
    movelist->capacity = DEFAULT_SIZE;
    movelist->num_moves = 0ul;
    movelist->moves = malloc(sizeof(Move*) * DEFAULT_SIZE);
    return movelist;
}

void movelist_destroy(MoveList *movelist)
{
    free(movelist->moves);
    free(movelist);
}

size_t movelist_size(MoveList* movelist)
{
    return movelist->num_moves; 
}

void movelist_push(MoveList *movelist, Move *move)
{
    if (movelist->num_moves == movelist->capacity) {
        movelist->capacity *= GROWTH_RATE; 
        movelist->moves = realloc(movelist->moves, 
                movelist->capacity * sizeof(Move));
    }

    movelist->moves[movelist->num_moves++] = move;
}

Move* movelist_get(MoveList* movelist, size_t idx)
{
    if (idx > movelist->num_moves - 1)
        return NULL;
    return movelist->moves[idx];
}
