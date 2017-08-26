#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#ifndef _GC_MALLOC_H_
#define _GC_MALLOC_H_

/**
  GC Malloc
  CS 283 - System Programming
  Drexel University
  */

// for memory allocation
#define MIN_BLOCK_SIZE sizeof(block)
#define MAX_BLOCKS_TO_ALLOCATE 5
typedef struct block
{
    size_t size;
    unsigned int mark;
    struct block* next;
    void* memory;
} block;



// object create
void *new_object(size_t size);

// malloc and free
block* findFreeBlock(block** last, size_t size);
block* requestAndExpand(block* last, size_t size);
void merge();
void* gc_malloc(size_t size);
void gc_free(void* p);

// mark and sweep
void mark(block* obj);
void sweep(block* obj);

void *block_init(size_t size);
#endif
