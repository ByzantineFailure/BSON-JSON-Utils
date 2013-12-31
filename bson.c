#include "bson.h"
#include "bson_JSONToBSON.h"

char *bson_JSONtoBSON(char *JSON)
{
	int JSON_length = strlen(JSON);
	char *BSON;
	Document *parsed = bson_parseJSON(JSON, JSON_length);
	
	BSON = convertParseToBSON(parsed);
	
	return BSON;
}

Document *bson_parseBSON(char *BSON)
{

}

char *bson_BSONtoJSON(char *BSON)
{

}

char *bson_convertParseToBSON(*bson_Document parse)
{

}

char *bson_convertParseToJSON(*bson_Document parse){

}

bson_element *bson_findElemenByName(*bson_Document parse){

}
