#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "minheap.h"

#define SBRK (4096)

minheap overall_heap = {NULL, NULL, 0};

void remove_node(heap_node *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->previous == NULL)
    {
        overall_heap.root = node->next;
    }
    else
    {
        node->previous->next = node->next;
    }

    if (node->next == NULL)
    {
        overall_heap.last = node->previous;
    }
    else
    {
        node->next->previous = node->previous;
    }

    // reassign
    node->next = NULL;
    node->previous = NULL;

    overall_heap.size -= 1;
}

void free_node(int size, void *ptr)
{
    insert_node(ptr, size);
}

// insert node into minheap FOLLOWING LOGIC
void insert_node(char *start_ptr, int size)
{
    heap_node *new_node = (heap_node *)start_ptr;

    new_node->size = size;
    new_node->start_ptr = (char *)start_ptr + sizeof(heap_node);
    new_node->previous = NULL;
    new_node->next = NULL;

    if (overall_heap.root == NULL)
    {
        overall_heap.root = new_node;
        overall_heap.last = new_node;
    }
    else
    // minheap logic https://www.geeksforgeeks.org/introduction-to-min-heap-data-structure/
    {
        heap_node *current = overall_heap.root;
        heap_node *previous = NULL;

        while (current != NULL && current->size < size)
        {
            previous = current;
            current = current->next;
        }
        if (previous == NULL)
        {
            new_node->next = overall_heap.root;
            overall_heap.root->previous = new_node;
            overall_heap.root = new_node;
        }
        else if (current == NULL)
        {
            previous->next = new_node;
            new_node->previous = previous;
            overall_heap.last = new_node;
        }
        else
        {
            new_node->next = current;
            new_node->previous = previous;
            previous->next = new_node;
            current->previous = new_node;
        }
    }

    overall_heap.size += 1;
}

// give back the smallest node of memory
void *get_node(int size)
{
    heap_node *current = overall_heap.root;
    heap_node *previous = NULL;

    while (current != NULL)
    {
        if (current->size >= size + sizeof(heap_node))
        {
            void *ptr_node = current->start_ptr;

            if (current->size == size)
            {
                remove_node(current);
                return ptr_node;
            }
            else
            {
                // Align the new pointer and ensure correct size adjustment
                size_t total_size = size + sizeof(heap_node);
                current->start_ptr += total_size;
                current->size -= total_size;
                return ptr_node;
            }
        }
        current = current->next;
    }

    void *ptr = get_heap_size(SBRK);

    heap_node *new_node = (heap_node *)ptr;
    new_node->size = SBRK - sizeof(heap_node);
    new_node->start_ptr = ptr;
    new_node->previous = NULL;
    new_node->next = NULL;

    insert_node(new_node->size, (char *)new_node);

    return get_node(size);
}

void *get_heap_size(size_t size)
{
    void *ptr = sbrk(0);
    sbrk(size);
    return ptr;
}