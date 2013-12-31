#include "bson_JSONToBSON.h"
#include "bson.h"

#define COMMA_SUCCESS_END_OF_OBJECT 2
#define COMMA_SUCCESS_HAS_COMMA 1
#define COMMA_FAILED -1

#define LENGTH_OF_TRUE 4
#define LENGTH_OF_FALSE 5
#define LENGTH_OF_NULL 4

#define ARRAY_RETURNABLE_OR_NEEDS_COMMA 1
#define ARRAY_HAS_COMMA_UNRETURNABLE 2

#define NUMBER_IS_VALID_NON_EXPONENT 1
#define NUMBER_IS_VALID_EXPONENT 2
#define NUMBER_IS_COMMA_OR_WHITESPACE 3
#define NUMBER_IS_INVALID -1

#define HEX_ESCAPE_LENGTH 4
#define HEX_RESULT_VALID_HEX 1
#define HEX_RESULT_INVALID_HEX -1

#define JSON_OBJECT_INVALID -1

int json_checkValidArray(char *JSONArray);
int json_checkValidValue(char *JSON);
int json_checkValidPair(char *JSON);
int json_checkValidString(char *JSON);
int json_checkValidNumber(char *JSON);
int json_isValidNumberCharacter(char check, int firstChar, int hasExponent)
int json_checkNextFourCharsForHex(char *JSON)

bson_Document *bson_parseJSON(char *JSON, int JSON_length)
{
	
}

//Returns length of object if successful, -1 if not
int json_checkValidJSON(char *JSON)
{
	int i, length, objlen, breakLoop, commaSuccess;
	char currentChar;
	objlen = strlen(JSON);
	//i = 1 because opening {
	i = 1;
	breakLoop = 0;
	checkForComma = 0;
	commaSuccess = 0;

	//Check opening {
	if(*(JSON) != '{')
		return JSON_OBJECT_INVALID;

	while(i < objlen)
	{
		currentChar = *(JSON + i);
		switch(currentChar)
		{
			//Whitespace, newlines, and tabs are a-okay
			case ' ':
			case '\n':
			case '\t':
				i++;
				break;
			//End of Object
			case '}':
				if(commaSuccess == COMMA_SUCCESS_HAS_COMMA)
					return JSON_OBJECT_INVALID;
				else
				{
					i++;
					breakLoop = 1;
					break;
				}
			//Pair.  Pairs must start with a string.
			case '\"':
				commaSuccess = 0;
				//Pass start of name string (including quote)
				length = json_checkValidPair(JSON + i);
				//Pair invalid
				if(length == JSON_OBJECT_INVALID)
				{
					breakLoop = 1;
					i = JSON_OBJECT_INVALID;
					break;
				}
				//Check for a comma or end of object
				else
				{
					i += length;
					while(i < objlen)
					{
						currentChar = *(JSON + i);
						switch(currentChar)
						{
							case: ','
								i++;
								commaSuccess = COMMA_SUCCESS_HAS_COMMA;
								break;
							//Don't increment i here, let outer loop hit the } so we don't duplicate logic
							case: '}'
								commaSuccess = COMMA_SUCCESS_END_OF_OBJECT;
								break;
							//Ignore whitespace
							case: ' '
							case: '\n'
							case: '\t'
								i++;
								break;
							default:
								commaSuccess = COMMA_FAILED;
								breakLoop = 1;
								i = JSON_OBJECT_INVALID;
								break;
						}
						if(commaSuccess != 0)
							break;
					}
					//If we don't find a comma or end of object, break
					if(!(commaSuccess == COMMA_SUCCESS_END_OF_OBJECT || commaSuccess == COMMA_SUCCESS_HAS_COMMA))
					{
						i = JSON_OBJECT_INVALID;
						breakLoop = 1;
					}
				}
				break;
			default:
				i = JSON_OBJECT_INVALID;
				breakLoop = 1;
				break;
		}
		if(breakLoop)
			break;
	}
	return i;
}

//Returns length of pair if successful, -1 if not
//Pass pointer to start of pair
int json_checkValidPair(char *JSON)
{
	int i, length, objlen, hasColon;
	char currentChar;
	hasColon = 0;
	objlen = strlen(JSON);
	
	//Pass start of name string (including quote)	
	i = json_checkValidString(JSON);
	if(i == JSON_OBJECT_INVALID)
		return JSON_OBJECT_INVALID;

	while(i < objlen && i != -1)
	{
		currentChar = *(JSON + i);
		switch(currentChar)
		{
			case ' ':
			case '\t':
			case '\n':
				i++;
				break;
			case ':':
				hasColon = 1;
				i++;
				break;
			default:
				return JSON_OBJECT_INVALID;
				break;
		}
		if(hasColon)
			break;
	}

	length += json_checkValidValue(JSON + i);
	if(length == JSON_OBJECT_INVALID)
		i = JSON_OBJECT_INVALID;
	else
		i += length;
	
	return i;
}	

int json_checkValidValue(char *JSON)
{
	char currentChar;
	int i, breakLoop, objLen, length;
	i = 0;
	breakLoop = 0;
	length = -1;
	objLen = strlen(JSON);
	
	while(i < objLen && i != -1 && breakLoop == 0)
	{
		currentChar = *(JSON + i);
		switch(currentChar)
		{
			case '\"':
				breakLoop = 1;
				length = json_checkValidString(JSON + i);
				i++;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '-':
				breakLoop = 1;
				length = json_checkValidNumber(JSON + i);
				i++;
				break;
			case '[':
				breakLoop = 1;
				length = json_checkValidArray(JSON + i);
				i++;
				break;
			case '{':
				breakLoop = 1;
				length = json_checkValidObject(JSON + i);
				break;
			case 't':
				breakLoop = 1;
				if(*(JSON + i + 1) != 'r' || *(JSON + i + 2) != 'u'
					|| *(JSON + i +3) != 'e')
					i = JSON_OBJECT_INVALID;
				else
					length = LENGTH_OF_TRUE;
				break;
			case 'f':
				breakLoop = 1;
				if(*(JSON + i + 1) != 'a' || *(JSON + i + 2) != 'l'
					|| *(JSON + i + 3) != 's' || *(JSON + i + 4) != 'e')
					i = JSON_OBJECT_INVALID;
				else
					length = LENGTH_OF_FALSE;
			case 'n':
				breakLoop = 1;
				if(*(JSON + i + 1) != 'u' || *(JSON + i + 2) != 'l'
					|| *(JSON + i + 3) != 'l')
					i = JSON_OBJECT_INVALID;
				else
					length = LENGTH_OF_NULL;
			case ' ':
			case '\n':
			case '\t':
				i++;
				break;
			default:
				breakLoop = 1;
				break;
		}
	}
	if(length != -1)
		return i + length;
	else
		return JSON_OBJECT_INVALID;
}

//Returns length of array if successful, -1 if not
//Pass pointer to start of array
int json_checkValidArray(char *JSONArray)
{
	int i, length, objlen, needsComma;
	char currentChar;
	i = 1;
	needsComma = 0;
	objlen = strlen(JSONArray);

	if(*(JSONArray) != '[')
		return JSON_OBJECT_INVALID;
	
	while(i < objlen)
	{
		currentChar = *(JSONArray + i);	
		switch(currentChar)
		{
			case ' ':
			case '\n':
			case '\t':
				i++;
				break;
			case ',':
				if(needsComma == ARRAY_RETURNABLE_OR_NEEDS_COMMA)
				{
					needsComma = ARRAY_HAS_COMMA_UNRETURNABLE;
					i++;
					break;
				}
				else
				{
					return JSON_OBJECT_INVALID;
				}
			case ']':
				if(needsComma == ARRAY_RETURNABLE_OR_NEEDS_COMMA)
					return i++;
				else
					return JSON_OBJECT_INVALID;
			default:
				if(needsComma == ARRAY_RETURNABLE_OR_NEEDS_COMMA)
					return JSON_OBJECT_INVALID;
			
				length = json_checkValue(JSONArray + i);
				
				if(length = JSON_OBJECT_INVALID)
					return length;
				else
					i += length;
					needsComma = ARRAY_RETURNABLE_OR_NEEDS_COMMA;
		}
	}	
}

//Returns length of string if valid, -1 if not
//Pass pointer to start of String
int json_checkValidString(char *JSON)
{
	int i, hexResult, length, objlen;
	char currentChar;
	i = 1;
	objlen = strlen(JSON);

	if(*(JSON) != '\"')
		return JSON_OBJECT_INVALID;
	
	while(i < objlen)
	{
		currentChar = *(JSON + i);	
		switch(currentChar)
		{
			case '\\':
				i++;
				currentChar = *(JSON + i);
				switch(currentChar)
				{
					case '\\':
					case '\"':
					case '/':
					case 'b':
					case 'f':
					case 'n':
					case 'r':
					case 't':
						i++;
						break;
					case 'u':
						hexResult = json_checkNextFourCharsForHex(JSON + i);
						if(hexResult = JSON_OBJECT_INVALID)
							return JSON_OBJECT_INVALID;
						
						i += HEX_ESCAPE_LENGTH;
						i++;
						break;
					default:
						return JSON_OBJECT_INVALID;
				}
			case '\"':
				i++;
				return i;
			default:
				i++;
		}
	}
}

//Returns length of string if valid, -1 if not
//Pass pointer to start of String
int json_checkValidNumber(char *JSON)
{
	int i, length, objlen, firstChar, hasExponent;
	char currentChar;
	i = 0;
	hasExponent = 0;
	firstChar = 1;
	objlen = strlen(JSON);

	while(i < objlen)
	{
		currentChar = *(JSON + i);
		switch(json_isValidNumberCharacter(currentChar, firstChar, hasExponent))
		{
			case NUMBER_IS_VALID_EXPONENT:
				hasExponent = 1;
				firstChar = 1;
				i++;
				break;
			case NUMBER_IS_VALID_NONEXPONENT:
				firstChar = 0;
				i++;	
				break;
			case NUMBER_IS_INVALID:
				return JSON_OBJECT_INVALID;
			case NUMBER_IS_COMMA_OR_WHITESPACE:
				return i;
			
		}
	}
	return JSON_OBJECT_INVALID;	
}

int json_isValidNumberCharacter(char check, int firstChar, int hasExponent)
{
	switch(check)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return NUMBER_IS_VALID_NONEXPONENT;
		case 'e':
		case 'E':
			if(!firstChar && !hasExponent)
				return NUMBER_IS_VALID_EXPONENT;
			else
				return NUMBER_IS_INVALID;
		case '-':
		case '+':
			if(firstChar)
				return NUMBER_IS_VALID_NONEXPONENT;
			else
				return NUMBER_IS_INVALID;
		case ' ':
		case '\n':
		case '\t':
		case ',':
			return NUMBER_IS_COMMA_OR_WHITESPACE;
		default:
			return NUMBER_IS_INVALID;
	}
}

int json_checkNextFourCharsForHex(char *JSON)
{
	int i;

	for(i = 1; i < 5; i++)
	{
		switch(*(JSON + i))
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case 'a':
			case 'A':
			case 'b':
			case 'B':
			case 'c':
			case 'C':
			case 'd':
			case 'D':
			case 'e':
			case 'E':
			case 'f':
			case 'F':
				break;
			default:
				return HEX_RESULT_INVALID_HEX;
		}
	}
	return HEX_RESULT_VALID_HEX;
}
