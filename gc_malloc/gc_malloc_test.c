#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "gc_malloc.h"

void gc_malloc_and_free_test();

int main(void)
{
	gc_malloc_and_free_test();
	return 0;
}

void gc_malloc_and_free_test()
{
	int *p1, *p2, *p3;

	p1 = (int*)gc_malloc(sizeof(int));
	printf("Address of p1 = %p | sizeof(p1) = %ld\n", p1, sizeof(p1));
	p2 = (int*)gc_malloc(sizeof(int));
	printf("Address of p2 = %p | sizeof(p2) = %ld\n", p2, sizeof(p2));
	p3 = (int*)gc_malloc(sizeof(int));
	printf("Address of p3 = %p | sizeof(p3) = %ld\n", p3, sizeof(p3));

	assert(sizeof(p1) == 8);
	assert(sizeof(p2) == 8);
	assert(sizeof(p3) == 8);
	
	gc_free(p1);
	printf("Address of p1 = %p | sizeof(p1) = %ld\n", p1, sizeof(p1));
	gc_free(p2);
	gc_free(p3);

	printf("gc_malloc_test: Successful\n");
}
