#include <stdlib.h>
#include "object.h"
#include "vm.h"

void gc(VM* vm)
{
	int numObjects = vm->numObjects;

	markAll(vm);
	sweep(vm);
	vm->maxObjects = vm->numObjects * 2;
}
