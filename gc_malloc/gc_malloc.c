#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "gc_malloc.h"

#define MIN_BLOCK_SIZE sizeof(block)
//void* global_header = NULL;
block* free_list = NULL;

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

block* requestAndExpand(block* last, size_t size)
{
	uintptr_t b = (uintptr_t)sbrk(0);	
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

void* gc_malloc(size_t size)
{
	block* b;

	if (size <= 0) return NULL;

	if (!free_list)//!global_header) // this is the first request
	{
		if (!(b = requestAndExpand(NULL, size))) return NULL;
		//global_header = b;
		free_list = b;
	}
	else
	{
		block* tail = free_list;//global_header;
		if (!(b = findFreeBlock(&tail, size))) return NULL;
		else b->free = 0;
	}

	return (b + 1);
}

void gc_free(void* p)
{
	if (!p) return;

	block* b = (block*)p - 1; // find memory location of p
	if (b->free != 0) return; // return if already free
	b->free = 1; 		  // otherwise, free the block
}
