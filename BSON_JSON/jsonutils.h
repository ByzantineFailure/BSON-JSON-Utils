#ifndef STD_INCLUDES
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define STD_INCLUDES
#endif

#include "bson_dll.h" 

#ifndef BSON_STRUCT_INCLUDE
typedef struct bson_Document {
	int length;
	bson_dll *elements;
} bson_Document;

typedef struct bson_Element {
	char type;
	int nameLength;
	char *name;
	int dataLength;
	void *data;
} bson_Element;
#define BSON_STRUCT_INCLUDE
#endif

#define JSON_OBJECT_INVALID -1

bson_Document *bson_parseJSON(char *JSON, int JSON_length);

int json_checkValidJSON(char *JSON);
