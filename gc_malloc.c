#include <stdlib.h>
#include <stdio.h>
#include "gc_malloc.h"

/**
  GC Malloc
  CS 283 - System Programming
  Drexel University
  */

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
    block* current = global_header;
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
    block* b = sbrk(0);
    void* request;
    if ((request = sbrk(size + MIN_BLOCK_SIZE)) == (void*)-1)
        return NULL; // cannot request more memory

    if (last) last->next = b;

    b->size = size;
    b->next = NULL;
    b->free = 0;

    return b;
}

// malloc a block of memory
void* gc_malloc(size_t size)
{
    block* b;

    if (size <= 0) return NULL;

    if (!global_header) // this is the first request
    {
        if (!(b = requestAndExpand(NULL, size))) return NULL;
        global_header = b;
    }
    else
    {
        block* tail = global_header;
        if (!(b = findFreeBlock(&tail, size))) return NULL;
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
    b->free = 1; 		      // otherwise, free the block
}

/*
 * Mark and Sweep
 */

// mark all the used memory
void mark()
{
    // loop through each reachable block
    
    // mark it as reachable
    
    // if threshold is reached, sweep
}

// free all the unmarked memory
void sweep()
{
    // loop through all blocks in memory

    // de-allocate ones that aren't marked
    //gc_free(...)
}

// recursively mark each block
void markAll()
{

}

