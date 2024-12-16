#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// define "x" for system malloc, include for our versions. Don't do both.
#ifndef SYSTEM_MALLOC
#define diff_free free
#define malloc_node malloc
#else
#include "memory_allocator.h"
#endif

int rand_between(int min, int max) { return rand() % (max - min + 1) + min; }

#define TEST_SIZE 30
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char *argv[])
{
  srand(time(NULL));

  char *test_string = "por el enjambre no esta pa aca, esta pa alla";

  if (argc > 1)
  {
    test_string = argv[1];
  }

  char *ptrs[TEST_SIZE] = {0};

  for (int ix = 0; ix < TEST_SIZE; ix++)
  {
    int size = rand_between(1, 1024 * 300);

    fprintf(stderr, "[%d] malloc'ing %d bytes\n", ix, size);
    ptrs[ix] = malloc_node(size);
    if (ptrs[ix] == NULL)
    {
      printf("[%d] malloc_node failed\n", ix);
      exit(1);
    }

    int len_to_copy = MIN(strlen(test_string), size - 1);

    fprintf(stderr, "[%d] ptrs[%d]: %p, going to copy %d chars\n", ix, ix,
            ptrs[ix], len_to_copy);

    strncpy(ptrs[ix], test_string, len_to_copy);
    ptrs[ix][len_to_copy] = '\0';

    fprintf(stderr, "[%d] '%s'\n", ix, ptrs[ix]);

    if (rand_between(1, 100) <= 10)
    {
      int new_size = rand_between(1, 1024);
      fprintf(stderr, "[%d] reallocating %p to new size: %d\n", ix, ptrs[ix], new_size);
      char *new_ptr = realloc_node(ptrs[ix], new_size);
      if (new_ptr == NULL)
      {
        fprintf(stderr, "[%d] realloc failed\n", ix);
      }
      else
      {
        ptrs[ix] = new_ptr;
        fprintf(stderr, "[%d] realloc'ed %p to new size: %d\n", ix, ptrs[ix], new_size);
      }
    }

    int index_to_free = rand_between(0, ix);
    if (ptrs[index_to_free])
    {
      fprintf(stderr, "\n[%d] randomly freeing %p ('%s')\n", index_to_free,
              ptrs[index_to_free], ptrs[index_to_free]);
      diff_free(ptrs[index_to_free]);
      fprintf(stderr, "[%d] freed %p\n", index_to_free, ptrs[index_to_free]);
      ptrs[index_to_free] = NULL;
    }
  }

  for (int ix = 0; ix < TEST_SIZE; ix++)
  {
    if (ptrs[ix])
    {
      fprintf(stderr, "[%d] freeing %p (%s)\n", ix, ptrs[ix], ptrs[ix]);
      diff_free(ptrs[ix]);
      fprintf(stderr, "[%d] freed %p\n", ix, ptrs[ix]);
    }
    else
    {
      fprintf(stderr, "[%d] already freed\n", ix);
    }
  }

  return 0;
}
