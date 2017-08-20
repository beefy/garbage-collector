#include "gc_malloc.h"

/**
  GC Malloc
  CS 283 - System Programming
  Drexel University
  */

block* allocated_memory = NULL;

/*
 * Object Create
 */

// create a new object in memory
void new_object(void* p) {
    // call gc_malloc

    // push to internal struct
}

/*
 * Malloc and Free functions
 */

// find and free a block of memory
block* findFreeBlock(block** last, size_t size)
{
    block* current = free_list;
    while (current && (!(current->free) || current->size < size))
    {
        *last = current;
        current = current->next;
    }

    return current;
}

// expand the memory allocated for this process
block* requestAndExpand(block* last, size_t size)
{
    uintptr_t b = (uintptr_t)sbrk(0); // find top of heap
    uintptr_t request = (uintptr_t)sbrk(size + MIN_BLOCK_SIZE);
    if (request == (uintptr_t)-1 || b != request)
        return NULL; // cannot request more memory

    if (last) last->next = (block*)b;

    ((block*)b)->size = size;
    ((block*)b)->next = NULL;
    ((block*)b)->free = 0;

    return (block*)b;
}

void merge()
{
    block *current;
    for (current = free_list; current != NULL; current = current->next)
    {
        if (current->next && (current->free && current->next->free))
        {
            current->size += current->next->size + sizeof(block); // increment block size to reflect merge
            current->next = current->next->next; // absorb next block into current block
        }
    }
}

// malloc a block of memory
void* gc_malloc(size_t size)
{
    block* b;

    if (size <= 0) return NULL;

    if (!free_list)// this is the first request
    {
        if (!(b = requestAndExpand(NULL, size))) return NULL;
        free_list = b;
    }
    else
    {
        block* tail = free_list;
        if (!(b = findFreeBlock(&tail, size)))
            if (!(b = requestAndExpand(tail, size))) return NULL;
            else b->free = 0;
    }

    return (b + 1);
}

// free an object
void gc_free(void* p)
{
    if (!p) return;

    block* b = (block*)p - 1; // find memory location of p
    if (b->free != 0) return; // return if already free
    b->free = 1; 		  // otherwise, free the block
    merge();
}

/*
 * Mark and Sweep
 */

// mark all reachable memory
void mark(block obj)
{
    // base case
    if (obj == NULL) return;
    // mark
    obj.mark = 1;
    // recurse
    return mark(obj.next);
}


// free all the unmarked memory
void sweep(block obj)
{
    // base case
    if (obj == NULL) return;
    // sweep
    if (!obj.mark) gc_free(obj.memory);
    // recurse
    return sweep(obj.next);
}

