#include "../BSON_JSON/jsonutils.h"

#define TEST_PASSED 1
#define TEST_FAILED 0

#define DEFAULT_TEST_JSON_SIZE 2048

#define VALID_EMPTY_OBJECT "{}"
#define VALID_EMPTY_OBJECT_LENGTH 2
#define VALID_STRING_OBJECT "{\"TestName\" : \"Hi There\"}"
#define VALID_STRING_OBJECT_LENGTH 25
#define VALID_CTRL_CHAR_STRING_OBJECT_NEWLINE "{\"TestName\" : \"Hi There \\n\"}"
#define VALID_CTRL_CHAR_STRING_OBJECT_NEWLINE_LENGTH 28
#define VALID_STRING_OBJECT_HEX "{\"TestName\" : \"Hi There \\uf01d \\u0123hexyhexhex\"}"
#define VALID_STRING_OBJECT_HEX_LENGTH 49

#define VALID_NUMBER_OBJECT "{\"TestName\" : 12345678 }"
#define VALID_NUMBER_OBJECT_LENGTH 24
#define VALID_NUMBER_OBJECT_NEGATIVE "{\"TestName\" : -12345678 }"
#define VALID_NUMBER_OBJECT_NEGATIVE_LENGTH 25
#define VALID_NUMBER_OBJECT_EXPONENT "{\"TestName\" : 12345678e15 }"
#define VALID_NUMBER_OBJECT_EXPONENT_LENGTH 27
#define VALID_NUMBER_OBJECT_NEGATIVE_EXPONENT "{\"TestName\" : 12345678e-15 }"
#define VALID_NUMBER_OBJECT_NEGATIVE_EXPONENT_LENGTH 28
#define VALID_NUMBER_OBJECT_NEGATIVE_WITH_EXPONENT "{\"TestName\" : -12345678e15 }"
#define VALID_NUMBER_OBJECT_NEGATIVE_WITH_EXPONENT_LENGTH 28
#define VALID_NUMBER_OBJECT_NEGATIVE_WITH_NEGATIVE_EXPONENT "{\"TestName\" : -12345678e-15 }"
#define VALID_NUMBER_OBJECT_NEGATIVE_WITH_NEGATIVE_EXPONENT_LENGTH 29
#define VALID_NUMBER_OBJECT_FRACTION "{\"TestName\" : 1234567.8 }" 
#define VALID_NUMBER_OBJECT_FRACTION_LENGTH 25

#define VALID_ARRAY_OBJECT_EMPTY "{\"TestArray\":[]}"
#define VALID_ARRAY_OBJECT_EMPTY_LENGTH 16 
#define VALID_ARRAY_OBJECT_NUMBERS "{ \"TestArray\" : [1, 2, 3] }"
#define VALID_ARRAY_OBJECT_NUMBERS_LENGTH 27
#define VALID_ARRAY_OBJECT_STRINGS "{ \"TestArray\" : [\"1\",\"2\", \"3\"] }"
#define VALID_ARRAY_OBJECT_STRINGS_LENGTH 32
#define VALID_ARRAY_OBJECT_ARRAYS "{ \"TestArray\" : [[1, 2, 3], [1, 2, 3], []] }"
#define VALID_ARRAY_OBJECT_ARRAYS_LENGTH  44
#define VALID_ARRAY_OBJECT_OBJECTS "{ \"TestArray\" : [{}, {}, {\"TestArray\":[]}] }"
#define VALID_ARRAY_OBJECT_OBJECTS_LENGTH 44

#define VALID_MULTI_OBJECT_STRINGS "{\"TestName\" : \"String 1\", \"Test2\" : \"String 2\"}"
#define VALID_MULTI_OBJECT_STRINGS_LENGTH 47
#define VALID_MULTI_OBJECT_EVERYTHING "{ \"1\" : [1,2,3], \"2\" : \"String\" , \"3\" : 12345, \"4\" : {} }"
#define VALID_MULTI_OBJECT_EVERYTHING_LENGTH 57 

#define INVALID_EMPTY_OBJECT_COMMA "{,}"


#define printResult(verbose, fmt, ...) \
	do { \
		if(verbose) \
			fprintf(stdout, fmt, ##__VA_ARGS__); \
	} while(0)

int jsonvalidation_testValidEmptyObject(int verbose);
int jsonvalidation_testValidStringObjects(int verbose);
int jsonvalidation_testValidNumberObjects(int verbose);
int jsonvalidation_testValidArrayObjects(int verbose);
int jsonvalidation_testValidMultiObjects(int verbose);

void jsonvalidation_runTests(int verbose)
{
	int passed;

	passed = jsonvalidation_testValidEmptyObject(verbose);
	if(passed == TEST_PASSED)
		fprintf(stdout, "Empty Object Passed!\n");
	else
		fprintf(stdout, "Empty Object Failed!\n");

	passed = jsonvalidation_testValidStringObjects(verbose);
	if(passed == TEST_PASSED)
		fprintf(stdout, "String Objects Passed!\n");
	else
		fprintf(stdout, "String Objects Failed!\n");

	passed = jsonvalidation_testValidNumberObjects(verbose);
	if(passed == TEST_PASSED)
		fprintf(stdout, "Number Objects Passed!\n");
	else
		fprintf(stdout, "Number Objects Failed!\n");
	
	passed = jsonvalidation_testValidArrayObjects(verbose);
	if(passed == TEST_PASSED)
		fprintf(stdout, "Array Objects Passed!\n");
	else
		fprintf(stdout, "Array Objects Failed!\n");
	
	passed = jsonvalidation_testValidMultiObjects(verbose);
	if(passed == TEST_PASSED)
		fprintf(stdout, "Multi Objects Passed!\n");
	else
		fprintf(stdout, "Multi Objects Failed!\n");
}

int jsonvalidation_testValidEmptyObject(int verbose)
{
	char *JSON = (char *)malloc(sizeof(char) * DEFAULT_TEST_JSON_SIZE);
	strcpy(JSON, VALID_EMPTY_OBJECT);
	int checkResult = json_checkValidJSON(JSON);
	free(JSON);

	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Empty object test failed (object invalid)!\n");
		return TEST_FAILED;
	}
	else if(checkResult != VALID_EMPTY_OBJECT_LENGTH)
	{
		printResult(verbose, "Empty object test failed (bad length)!\n");
		return TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Empty object test passed!\n");
		return TEST_PASSED;
	}
}

int jsonvalidation_testValidStringObjects(int verbose)
{
	char *JSON = (char *)malloc(sizeof(char) * DEFAULT_TEST_JSON_SIZE);
	strcpy(JSON, VALID_STRING_OBJECT);
	int checkResult = json_checkValidJSON(JSON);
	int testResult = TEST_PASSED;
	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Basic string object test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_STRING_OBJECT_LENGTH)
	{
		printResult(verbose, "Basic string object test failed (bad length)! Returned length was %d expected %d\n", 
				checkResult, VALID_STRING_OBJECT_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Basic string object test passed!\n");
	}

	strcpy(JSON, VALID_CTRL_CHAR_STRING_OBJECT_NEWLINE);
	checkResult = json_checkValidJSON(JSON);

	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Control Character (newline)string test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_CTRL_CHAR_STRING_OBJECT_NEWLINE_LENGTH)
	{
		printResult(verbose, "Control Character (newline) string test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_CTRL_CHAR_STRING_OBJECT_NEWLINE_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Control Character (newline) string test passed!\n");
	}

	strcpy(JSON, VALID_STRING_OBJECT_HEX);
	checkResult = json_checkValidJSON(JSON);

	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Hex string test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_STRING_OBJECT_HEX_LENGTH)
	{
		printResult(verbose, "Hex string test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_STRING_OBJECT_HEX_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Hex string test passed!\n");
	}

	free(JSON);
	return testResult;
}

int jsonvalidation_testValidNumberObjects(int verbose)
{
	char *JSON = (char *)malloc(sizeof(char) * DEFAULT_TEST_JSON_SIZE);
	strcpy(JSON, VALID_NUMBER_OBJECT);
	int checkResult = json_checkValidJSON(JSON);
	int testResult = TEST_PASSED;
	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Basic number test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_NUMBER_OBJECT_LENGTH)
	{
		printResult(verbose, "Basic number test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_NUMBER_OBJECT_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Basic number test passed!\n");
	}
	
	strcpy(JSON, VALID_NUMBER_OBJECT_NEGATIVE);
	checkResult = json_checkValidJSON(JSON);

	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Negative number test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_NUMBER_OBJECT_NEGATIVE_LENGTH)
	{
		printResult(verbose, "Negative number test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_NUMBER_OBJECT_NEGATIVE_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Negative number test passed!\n");
	}

	strcpy(JSON, VALID_NUMBER_OBJECT_EXPONENT);
	checkResult = json_checkValidJSON(JSON);

	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Positive exponent number test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_NUMBER_OBJECT_EXPONENT_LENGTH)
	{
		printResult(verbose, "Positive exponent number test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_NUMBER_OBJECT_EXPONENT_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Positive exponent number test passed!\n");
	}

	strcpy(JSON, VALID_NUMBER_OBJECT_NEGATIVE_EXPONENT);
	checkResult = json_checkValidJSON(JSON);

	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Negative exponent number test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_NUMBER_OBJECT_NEGATIVE_EXPONENT_LENGTH)
	{
		printResult(verbose, "Negative exponent number test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_NUMBER_OBJECT_NEGATIVE_EXPONENT_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Negative exponent number test passed!\n");
	}
	
	strcpy(JSON, VALID_NUMBER_OBJECT_NEGATIVE_WITH_EXPONENT); 
	checkResult = json_checkValidJSON(JSON);

	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Negative with exponent number test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_NUMBER_OBJECT_NEGATIVE_WITH_EXPONENT_LENGTH)
	{
		printResult(verbose, "Negative with exponent number test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_NUMBER_OBJECT_NEGATIVE_WITH_EXPONENT_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Negative with exponent number test passed!\n");
	}

	strcpy(JSON, VALID_NUMBER_OBJECT_NEGATIVE_WITH_NEGATIVE_EXPONENT); 
	checkResult = json_checkValidJSON(JSON);

	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Negative with negative exponent number test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_NUMBER_OBJECT_NEGATIVE_WITH_NEGATIVE_EXPONENT_LENGTH)
	{
		printResult(verbose, "Negative with negative exponent number test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_NUMBER_OBJECT_NEGATIVE_WITH_NEGATIVE_EXPONENT_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Negative with negative exponent number test passed!\n");
	}
	
	strcpy(JSON, VALID_NUMBER_OBJECT_FRACTION);
	checkResult = json_checkValidJSON(JSON);
	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Fraction number test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_NUMBER_OBJECT_FRACTION_LENGTH)
	{
		printResult(verbose, "Fraction number test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_NUMBER_OBJECT_FRACTION_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Fraction number test passed!\n");
	}

	free(JSON);
	return testResult;
}

int jsonvalidation_testValidArrayObjects(int verbose)
{
	char *JSON = (char *)malloc(sizeof(char) * DEFAULT_TEST_JSON_SIZE);
	strcpy(JSON, VALID_ARRAY_OBJECT_EMPTY);
	int checkResult = json_checkValidJSON(JSON);
	int testResult = TEST_PASSED;
	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Empty array test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_ARRAY_OBJECT_EMPTY_LENGTH)
	{
		printResult(verbose, "Empty array test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_ARRAY_OBJECT_EMPTY_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Empty array test passed!\n");
	}
	
	strcpy(JSON, VALID_ARRAY_OBJECT_NUMBERS);
	checkResult = json_checkValidJSON(JSON);
	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Numbers array test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_ARRAY_OBJECT_NUMBERS_LENGTH)
	{
		printResult(verbose, "Numbers array test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_ARRAY_OBJECT_NUMBERS_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Numbers array test passed!\n");
	}
	
	strcpy(JSON, VALID_ARRAY_OBJECT_STRINGS);
	checkResult = json_checkValidJSON(JSON);
	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Strings array test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_ARRAY_OBJECT_STRINGS_LENGTH)
	{
		printResult(verbose, "Strings array test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_ARRAY_OBJECT_STRINGS_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Strings array test passed!\n");
	}
	
	strcpy(JSON, VALID_ARRAY_OBJECT_ARRAYS);
	checkResult = json_checkValidJSON(JSON);
	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Arrays array test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_ARRAY_OBJECT_ARRAYS_LENGTH)
	{
		printResult(verbose, "Arrays array test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_ARRAY_OBJECT_ARRAYS_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Arrays array test passed!\n");
	}
	
	strcpy(JSON, VALID_ARRAY_OBJECT_OBJECTS);
	checkResult = json_checkValidJSON(JSON);
	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Objects array test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_ARRAY_OBJECT_OBJECTS_LENGTH)
	{
		printResult(verbose, "Objects array test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_ARRAY_OBJECT_OBJECTS_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Objects array test passed!\n");
	}
	free(JSON);
	return testResult;	
}

int jsonvalidation_testValidMultiObjects(int verbose)
{
	char *JSON = (char *)malloc(sizeof(char) * DEFAULT_TEST_JSON_SIZE);
	strcpy(JSON, VALID_MULTI_OBJECT_STRINGS);
	int checkResult = json_checkValidJSON(JSON);
	int testResult = TEST_PASSED;

	
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Multi-object Strings test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_MULTI_OBJECT_STRINGS_LENGTH)
	{
		printResult(verbose, "Multi-object Strings test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_MULTI_OBJECT_STRINGS_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Multi-object Strings test passed!\n");
	}
	
	strcpy(JSON, VALID_MULTI_OBJECT_EVERYTHING);
	checkResult = json_checkValidJSON(JSON);
	if(checkResult == JSON_OBJECT_INVALID)
	{
		printResult(verbose, "Multi-object Everything test failed (object invalid)!\n");
		testResult = TEST_FAILED;
	}
	else if(checkResult != VALID_MULTI_OBJECT_EVERYTHING_LENGTH)
	{
		printResult(verbose, "Multi-object Everything test failed (bad length)! Returned length was %d expected %d\n",
				checkResult, VALID_MULTI_OBJECT_EVERYTHING_LENGTH);
		testResult = TEST_FAILED;
	}
	else
	{
		printResult(verbose, "Multi-object Everything test passed!\n");
	}
	free(JSON);
	return testResult;	
}
