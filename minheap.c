#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "minheap.h"

#define SBRK (4096)

minheap overall_heap;

void remove_node(heap_node *node)
{
    if (node == NULL) {
        return;
    }
    if (node->previous == NULL) {

    }
    
}

void free_node(int size, void *ptr)
{

}