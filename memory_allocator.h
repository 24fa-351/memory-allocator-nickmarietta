#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <stdlib.h>

char* calloc_node(size_t someNum, size_t size);

void* realloc_node(void *ptr, size_t size);

char* malloc_node(size_t size);

void diff_free(void *ptr);

#endif