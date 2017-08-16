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
typedef struct block
{
    size_t size;
    unsigned int free;
    struct block* next;
} block;

// constants
#define MIN_BLOCK_SIZE sizeof(block)

// object create
void new_object(void* p);

// malloc and free
block* findFreeBlock(block** last, size_t size);
block* requestAndExpand(block* last, size_t size);
void merge();
void* gc_malloc(size_t size);
void gc_free(void* p);

// mark and sweep
void mark();
void sweep();
void markAll();

#endif
