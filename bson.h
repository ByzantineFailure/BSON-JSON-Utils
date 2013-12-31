#ifndef STD_INCLUDES
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define STD_INCLUDES
#endif

#ifndef BSON_INCLUDES
#include "bson_dll.h"
#include "bson_constants.h"
#define BSON_INCLUDES
#endif

#ifndef BSON_DEBUG_INCLUDE
#include "debuglog.h"
#define BSON_DEBUG_INCLUDE
#endif

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

char *bson_JSONtoBSON(char *JSON);
bson_Document *bson_parseBSON(char *BSON);
char *bson_BSONtoJSON(char *BSON);
char *bson_convertParseToBSON(*bson_Document parse);
char *bson_convertParseToJSON(*bson_Document parse);
bson_Element *bson_findElementByName(*bson_Document parse);
