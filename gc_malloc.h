#include <stdlib.h>
#include <stdio.h>

/**
  GC Malloc
  CS 283 - System Programming
  Drexel University
  */

/*
 * Structures and Constants
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
void* global_header = NULL;

/*
 * Object Create
 */

// main funcs
void new_object(void* p);

/*
 * Malloc and Free
 */

// main funcs
void* gc_malloc(size_t size);
void gc_free(void* p);

// helpers
block* findFreeBlock(block** last, size_t size);
block* requestAndExpand(block* last, size_t size);

/*
 * Mark and Sweep
 */

// main funcs
void mark();
void sweep();

// helpers
void markAll();

