#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#define DEFAULT_CAPACITY 10
#define MAX_CAPACTIY UINT_MAX - 1
#define GROWTH_RATE 2 // how much to increase the size of the list by

typedef struct {
    uint32_t capacity;
    uint32_t size;
    void** content;
} ArrayList;

ArrayList* arraylist_create();
void arraylist_destroy(ArrayList* list);
int arraylist_push(ArrayList* list, void* element);
void* arraylist_pop(ArrayList* list);
void* arraylist_get(ArrayList* list, uint32_t idx);
void arraylist_set(ArrayList* list, uint32_t idx, void* element);
void arraylist_insert(ArrayList* list, uint32_t idx, void* element);
void* arraylist_remove(ArrayList* list, uint32_t idx);

#endif
