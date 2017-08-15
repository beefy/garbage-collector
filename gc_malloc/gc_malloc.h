#ifndef _GC_MALLOC_H_
#define _GC_MALLOC_H_

typedef struct block
{
	size_t size;
	unsigned int free;
	struct block* next;
} block;

block* findFreeBlock(block** last, size_t size);
block* requestAndExpand(block* last, size_t size);
void merge();
void* gc_malloc(size_t size);
void gc_free(void* p);

#endif
