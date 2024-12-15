#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "minheap.h"

#define SBRK (4096)

minheap overall_heap = {NULL, NULL, 0};

void remove_node(heap_node *node)
{
    if (node == NULL) {
        return;
    }
    if (node->previous == NULL) {
        overall_heap.root = node->next;
    } else {
        node->previous->next = node->next;
    }
    
}

void free_node(int size, void *ptr)
{

}