#include <stdlib.h>
#include <stdio.h>

#define MIN_BLOCK_SIZE 4096

typedef struct block
{
	size_t size;
	unsigned int free;
	struct block* next;
} block;

void* global_header = NULL;

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
