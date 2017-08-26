#include "gc_malloc.h"

/**
  GC Malloc
  CS 283 - System Programming
  Drexel University
  */

block* allocated_memory = NULL;
int blocks_allocated = 0;

/*
 * Object Create
 */

// create a new object in memory
void *new_object(size_t size) {
    blocks_allocated++;
    if (blocks_allocated > MAX_BLOCKS_TO_ALLOCATE) {
        sweep(allocated_memory);
        blocks_allocated = 0;
    }

    // call gc_malloc
    return block_init(size);
    // push to internal struct
}

/*
 * Malloc and Free functions
 */

// find and free a block of memory
block* findFreeBlock(block** last, size_t size)
{
    block* current = allocated_memory;
    while (current && (!(current->mark) || current->size < size))
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

    return (block*)b;
}

void merge()
{
    block *current;
    for (current = allocated_memory; current != NULL; current = current->next)
    {
        if (current->next && (current->mark && current->next->mark))
        {
            // increment block size to reflect merge
            current->size += current->next->size + sizeof(block);
            // absorb next block into current block
            current->next = current->next->next;
        }
    }
}

// malloc a block of memory
void* gc_malloc(size_t size)
{
    void* b;

    if (size <= 0) return NULL;

    if (allocated_memory == NULL)
    {
        // this is the first request
        if (!(b = requestAndExpand(NULL, size))) return NULL;
    }
    else
    {
        block* tail = allocated_memory;
        if (!(b = findFreeBlock(&tail, size)))
	    {
	        if (!(b = requestAndExpand(tail, size))) return NULL;
	    }
    }

    return b;
}

// free an object
void gc_free(void* p)
{
    if (!p) return;

    block* b = (block*)p - 1; // find memory location of p
    if (b->mark != 0) return; // return if already free
    b->mark = 1; 		  // otherwise, free the block
    merge();
}

/*
 * Mark and Sweep
 */

// mark all reachable memory
void mark(block* obj)
{
    // base case
    if (obj == NULL) return;
    // mark
    obj->mark = 1;
    // recurse
    mark(obj->next);
    return;
}


// free all the unmarked memory
void sweep(block* obj)
{
    // base case
    if (obj == NULL) return;
    // sweep
    //    if (!obj->mark) gc_free(obj->memory);
    if (!obj->mark) gc_free(obj->memory);
    else obj->mark = 0;
    // recurse
    sweep(obj->next);
    return;
}

void *block_init(size_t size) {
    block *b = (block *)gc_malloc(sizeof(block));
    b->size = size;
    b->mark = 0;
    b->memory = gc_malloc(size);

    b->next = allocated_memory;

    return b->memory;
}
