#include "arraylist.h"

#include <stdlib.h>

// TODO add the extra functionality if needed: set, change size, pop changing
// capacity copy function, insert, remove, clear, etc...

ArrayList *arraylist_create()
{
    ArrayList *list = malloc(sizeof(ArrayList));
    if (!list)
        return NULL;
    list->capacity = DEFAULT_CAPACITY;
    list->size = 0;
    list->content = calloc(DEFAULT_CAPACITY, sizeof(void *));
    if (!list->content)
        return NULL;
    return list;
}


void destroy_list(ArrayList *list)
{
    free(list->content);
    free(list);
}


uint32_t size(ArrayList* list)
{
    return list->size;
}

ArrayListError push(ArrayList *list, void *element)
{
    if (!element)
        return NULL_ELEMENT_ERROR;

    if (list->capacity == MAX_CAPACTIY)
        return MAX_CAPACITY_ERROR;

    if (list->size == list->capacity - 1) {
        if (list->capacity >= MAX_CAPACTIY / GROWTH_RATE)
            list->capacity = MAX_CAPACTIY;
        else
            list->capacity *= GROWTH_RATE;
        list->content = realloc(list->content, list->capacity * sizeof(void*));
    }

    list->content[list->size++] = (void *)element;
    return 0;
}

void *pop(ArrayList *list)
{
    if (list->size == 0)
        return NULL;
    return list->content[list->size--];
}

void *get(ArrayList *list, uint32_t idx)
{
    if (idx > list->size)
        return NULL;
    return list->content[idx];
}

void set(ArrayList *list, uint32_t idx, void *element)
{
    list->content[idx] = element;
}
