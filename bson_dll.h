#ifndef STD_INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STD_INCLUDES
#endif

typedef struct bson_dll {
	bson_dll_node head;
} bson_dll;

typedef struct bson_dll_node {
	void *data;
	bson_dll_node *next;
	bson_dll_node *previous;
}

bson_dll *bson_dll_newList();

//Will free all data pointers, so make sure they don't have any children that need freeing
void bson_dll_destroy(bson_dll *list);

bson_dll_node *bson_dll_iterateNode(bson_dll_node *node);
bson_dll_node *bson_dll_append(bson_dll *addTo,void *data, int isList);
