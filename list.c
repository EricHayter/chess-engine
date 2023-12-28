#include <stdint.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 10
#define MAX_CAPACTIY sizeof(uint32_t) * 8 - 1
#define GROWTH_RATE 2 // how much to increase the size of the list by
                      // if the capacity is exceeded

// add some errors

struct List {
    size_t data_size;
    uint32_t capacity;
    uint32_t size;
    void* content;
};

int arraylist_init(struct List* l, size_t ds) {
    if (!l)
        return 1;
    l->data_size = ds;
    l->capacity = 10;
    l->size = 0;
    l->content = malloc(ds * DEFAULT_CAPACITY);
    if (!l->content)
        return 1;
    return 0;
}

void destroy_list(struct List* list) {
    free(list->content);
    free(list);
}

int push(struct List* list, void* element) {
    if (list->capacity == MAX_CAPACTIY)
        return 1; 

    if (list->size == list->capacity) {
        if (list->capacity >= MAX_CAPACTIY / GROWTH_RATE)
           list->capacity = MAX_CAPACTIY; 
        else
            list->capacity *= GROWTH_RATE;
        void* t = realloc(list->content ,list->data_size * list->capacity);
    } 

    list->content[list->size++] = element;
    return 0;
}

uint8_t pop(struct List* l) {
    return l->content[l->size--];
}
