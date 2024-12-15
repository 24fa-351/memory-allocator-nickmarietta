#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include "memory_allocator.h"
#include "minheap.h"

// need some type of structure to keep track of all the memory we've allocated
typedef struct
{
    void *ptr;
    size_t size;
} allocation_struct;

allocation_struct allocations[1000000];

size_t num_allocations = 0;

char *calloc_node(size_t someNum, size_t size)
{
    return malloc(someNum * size);
}

void *realloc_node(void *ptr, size_t size)
{
    for (int ix = 0; ix < num_allocations; ix++)
    {
        if (allocations[ix].ptr == ptr)
        {
            void *temp_ptr = malloc_node(size);
            if (temp_ptr == NULL)
            {
                fprintf(stderr, "realloc_node failed\n");
                return NULL;
            }
            size_t copy_size = (allocations[ix].size < size) ? allocations[ix].size : size;
            memcpy(temp_ptr, ptr, copy_size);

            diff_free(ptr);
            return temp_ptr;
        }
    }
}

char *malloc_node(size_t size)
{
    void *ptr = get_node(size);
    if (ptr == NULL)
    {
        fprintf(stderr, "malloc_node failed\n");
        exit(1);
    }

    fprintf(stderr, "malloc_node: %p\n", ptr);
    allocations[num_allocations].ptr = ptr;
    allocations[num_allocations].size = size;
    num_allocations += 1;

    return ptr;
}

void diff_free(void *ptr)
{
    for (int ix = 0; ix < num_allocations; ix++)
    {
        if (allocations[ix].ptr == ptr)
        {
            free_node(allocations[ix].size, ptr);
            allocations[ix].ptr = NULL;
            allocations[ix].size = 0;
            return;
        }
    }
}