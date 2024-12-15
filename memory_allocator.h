#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <stdlib.h>

void free_node(void *ptr);

char* calloc_node(void *ptr, size_t size);

void* realloc_node(void *ptr, size_t size);

char* malloc_node(size_t size);

#endif