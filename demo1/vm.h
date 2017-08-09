#ifndef _VM_H
#define _VM_H

#include <stdlib.h>
#include "object.h"

#define STACK_MAX 256

typedef struct 
{
	Object* stack[STACK_MAX];
	int numObjects;
	int maxObjects;
	int stackSize;
	Object* firstObject;
} VM;

VM* initVM();
Object* newObject(VM* vm, ObjectType type);
void push(VM* vm, Object* value);
void pushInt(VM* vm, int intValue);
Object* pushPair(VM* vm);
Object* pop(VM* vm);
void markAll(VM* vm);
void sweep(VM* vm);

#endif
