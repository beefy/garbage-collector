#include <stdlib.h>
#include "object.h"

void mark(Object* object)
{
	// if we already marked the object, exit
	if (object->marked) return;

	object->marked = 1;

	if (object->type == OBJ_PAIR)
	{
		mark(object->head);
		mark(object->tail);
	}
}
