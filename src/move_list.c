#include "move_list.h"
#include "move.h"
#include<assert.h>

MoveList *init_movelist()
{
	MoveList *movelist = malloc(sizeof(MoveList));
	movelist->len = 0;
	movelist->capacity = DEFAULT_CAPACITY;
	movelist->moves = malloc(sizeof(Move) * movelist->capacity);
	
	// if cannot allocate space for the moves then return null
	if (!movelist->moves)
		free(movelist);	

	return movelist;
}

void free_movelist(MoveList *movelist)
{
	// nothing to free on a null pointer
	if (!movelist)
		return;
	
	if (!movelist->moves)
		free(movelist->moves);

	free(movelist);
}

void add_move(MoveList *movelist, Move move)
{
	// can't handle null pointers
	if (!movelist)
		return;

	assert(movelist->len <= movelist->capacity);

	// if we are full
	if (movelist->len == movelist->capacity) {
		movelist->capacity *= GROWTH_RATE;
		movelist->moves = realloc(movelist->moves, sizeof(Move) * movelist->capacity);
	}
	movelist->moves[movelist->len++] = move;		
}
