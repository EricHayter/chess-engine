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
void destroy_list(ArrayList* list);
int push(ArrayList* list, void* element);
void* pop(ArrayList* list);
void* get(ArrayList* list, uint32_t idx);
void set(ArrayList* list, uint32_t idx, void* element);
void insert(ArrayList* list, uint32_t idx, void* element);
void* remove(ArrayList* list, uint32_t idx);

#endif
