#ifndef _OBJECT_H
#define _OBJECT_H

#include <stdlib.h>

typedef enum 
{
	OBJ_INT,
	OBJ_PAIR,
} ObjectType;

typedef struct sObject
{
	unsigned char marked;
	ObjectType type;
	union 
	{
		int value; // OBJ_INT
		struct // OBJ_PAIR
		{
			struct sObject* head;
			struct sObject* tail;
		};
	};
	struct sObject* next;
} Object;

void mark(Object* object);

#endif
