#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../gc_malloc/gc_malloc.h"

void gc_malloc_and_free_test();
void new_object_test();

// sizeof = 16
typedef struct mallocTest
{
    char* c;
    int x;
} mallocTest;

int main(void)
{
    // gc_malloc_and_free_test();
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
    mallocTest *p1 = NULL;
    printf("%p\n", p1);
    p1 = (mallocTest *)new_object(sizeof(mallocTest));
    printf("%p\n\n", p1);

    mallocTest *p2 = NULL;
    printf("%p\n", p2);
    p2 = (mallocTest *)new_object(sizeof(mallocTest));
    printf("%p\n\n", p2);

    mallocTest *p3 = NULL;
    printf("%p\n", p3);
    p3 = (mallocTest *)new_object(sizeof(mallocTest));
    printf("%p\n\n", p3);

    mallocTest *p4 = NULL;
    printf("%p\n", p4);
    p4 = (mallocTest *)new_object(sizeof(mallocTest));
    printf("%p\n\n", p4);

    mallocTest *p5 = NULL;
    printf("%p\n", p5);
    p5 = (mallocTest *)new_object(sizeof(mallocTest));
    printf("%p\n\n", p5);

    mallocTest *p6 = NULL;
    printf("%p\n", p6);
    p6 = (mallocTest *)new_object(sizeof(mallocTest));
    printf("%p\n\n", p6);

    mallocTest *p7 = NULL;
    printf("%p\n", p7);
    p7 = (mallocTest *)new_object(sizeof(mallocTest));
    printf("%p\n\n", p7);
}

