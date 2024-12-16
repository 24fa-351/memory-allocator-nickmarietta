#ifndef MINHEAP_H
#define MINHEAP_H

#include <stddef.h>

typedef unsigned long long heap_key;
typedef void heap_val;

// design of minheap node
typedef struct heap_node
{
    int size;
    char *start_ptr;
    struct heap_node *previous;
    struct heap_node *next;
} heap_node;

// actual minheap design
typedef struct
{
    heap_node *root;
    heap_node *last;
    heap_node data;
    size_t size;
} minheap;

void remove_node(heap_node *node);

void free_node(int size, void *ptr);

// start ptr here because of how we append to minheap
void insert_node(char *start_ptr, int size);

void *get_node(int size);

void *get_heap_size(size_t size);

#endif