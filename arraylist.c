#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <limits.h>

#define DEFAULT_CAPACITY 10
#define MAX_CAPACTIY UINT_MAX - 1
#define GROWTH_RATE 2 // how much to increase the size of the list by
                      // if the capacity is exceeded

int i = 0;

typedef struct {
    size_t data_size;
    uint32_t capacity;
    uint32_t size;
    void** content;
} ArrayList;

ArrayList* arraylist_create(size_t ds) {
    ArrayList* list = malloc(sizeof(ArrayList));
    list->data_size = ds;
    list->capacity = DEFAULT_CAPACITY;
    list->size = 0;
    list->content = calloc(DEFAULT_CAPACITY, sizeof(void *));
    if (!list->content)
        return NULL;
    return list;
}
void destroy_list(ArrayList* list) { free(list->content); free(list); }

int push(ArrayList* list, void* element) {
    assert((list != NULL) && "arraylist pointer is null");
    if (list->capacity == MAX_CAPACTIY)
        return 1; 

    if (list->size == list->capacity - 1) {
        if (list->capacity >= MAX_CAPACTIY / GROWTH_RATE)
           list->capacity = MAX_CAPACTIY; 
        else
            list->capacity *= GROWTH_RATE;
        list->content = realloc(list->content, list->capacity * sizeof(void *));
    } 

    list->content[list->size++] = (void *) element;
    return 0;
}

void* pop(ArrayList* list) {
    return list->content[list->size--];
}

void* get(ArrayList* list, uint32_t idx) {
    return list->content[idx];
}

void set(ArrayList* list, uint32_t idx, void* element) {
    list->content[idx] = element;
}

int main() {
    ArrayList* list = arraylist_create(sizeof(int));
    if (!list)
        return 1;


    for (int i = 0; i < 164; i++) {
        push(list, (void*)(intptr_t) i); 
    } 

    printf("Done\n");
    destroy_list(list);
}
