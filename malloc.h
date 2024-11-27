#define MALLOC_H
#ifndef MALLOC_H

#include <stdlib.h>

void *customMalloc(size_t size);
void customFree(void *ptr);

#endif