#include <stdlib.h>
#include <stdio.h>
#include "vm.h"
#include "object.h"

#define INITIAL_GC_THRESHOLD 15

VM* initVM()
{
	VM* vm = (VM*)malloc(sizeof(VM));
	vm->numObjects = 0;
	vm->maxObjects = INITIAL_GC_THRESHOLD;
	vm->stackSize = 0;
	vm->firstObject = NULL;

	return vm;
}

Object* newObject(VM* vm, ObjectType type)
{
	Object* object = (Object*)malloc(sizeof(Object));
	object->type = type;
	object->marked = 0;
	object->next = vm->firstObject;
	vm->firstObject = object;
	vm->numObjects++;

	return object;
}

void push(VM* vm, Object* value)
{
	if (vm->stackSize >= STACK_MAX)
	{
		fprintf(stderr, "Stack overflow!\n");
		return;
	}


	vm->stack[vm->stackSize++] = value;
}

void pushInt(VM* vm, int intValue)
{
	Object* object = newObject(vm, OBJ_INT);
	object->value = intValue;
	push(vm, object);
}

Object* pushPair(VM* vm)
{
	Object* object = newObject(vm, OBJ_PAIR);
	object->tail = pop(vm);
	object->head = pop(vm);
	push(vm, object);

	return object;
}

Object* pop(VM* vm)
{
	if (vm->stackSize <= 0) 
	{
		fprintf(stderr, "Stack underflow!\n");
		return NULL;
	}
	
	return vm->stack[--vm->stackSize];
}

void markAll(VM* vm)
{
	int i;
	for (i = 0; i < vm->stackSize; i++)
		mark(vm->stack[i]);
}

void sweep(VM* vm)
{
	Object** object = &vm->firstObject;
	while (*object)
	{
		if (!(*object)->marked) // remove and free unmarked object
		{
			Object* unreached = *object;
			*object = unreached->next;
			free(unreached);
			vm->numObjects--;
		}
		else // unmark object for next GC and move to next object
		{
			(*object)->marked = 0;
			object = &(*object)->next;
		}
	}
}
