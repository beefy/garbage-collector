#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../gc_malloc/gc_malloc.h"

void gc_malloc_and_free_test();
void new_object_test();

typedef struct mallocTest
{
    char* c;
    int x;
} mallocTest;

int main(void)
{
    gc_malloc_and_free_test();
    new_object_test();
    return 0;
}

void gc_malloc_and_free_test()
{
    mallocTest *mt1, *mt2, *mt3;
    mt1 = (mallocTest*)gc_malloc(sizeof(mallocTest));
    printf("Address of mt1 = %p\n", mt1);
    mt2 = (mallocTest*)gc_malloc(sizeof(mallocTest));
    printf("Address of mt2 = %p\n", mt2);

    void* ptr = mt1;
    printf("ptr = %p\n", ptr);
    gc_free(mt1);

    mt3 = (mallocTest*)gc_malloc(sizeof(mallocTest));
    printf("Address of mt3 = %p\n", mt3);
    assert(mt3 == ptr); // assert that we successfully reused mem location at mt1

    gc_free(mt2);
    gc_free(mt3);

    printf("gc_malloc_test: Successful\n");
}

void new_object_test() {
    mallocTest *p[10];
    new_object(p[0], sizeof(p));
    printf("new object successfully allocated.\n");
    printf("address of new object: %p\n", p[0]);
    int i;
    printf("creating more new objects\n");
    for (i = 1; i < 10; i++) {
        printf("creating object #%d\n", i);
        new_object(p[i], sizeof(p));
        printf("new object successfully allocated.\n");
        printf("address of new object: %p\n", p[i]);
    }
}
