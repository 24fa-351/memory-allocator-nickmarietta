// final implementation to be minheap

#define HEAP_H
#ifndef HEAP_H

typedef unsigned long long heap_key;
typedef void heap_val;

// design of minheap node
typedef struct
{
    heap_key key;
    heap_val *val;
} heap_node;

typedef struct
{
    heap_node *nodes;
    int size;
    int capacity;
} custom_heap;

custom_heap *heap_init(unsigned int capacity);

void free_heap(custom_heap *heap);

unsigned int heap_size(custom_heap *heap);

void heap_insert(custom_heap *heap, heap_key key, heap_val *val);

#endif