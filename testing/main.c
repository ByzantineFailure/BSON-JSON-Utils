#include "../debugUtils/printutils.h"
#include "../BSON_JSON/jsonutils.h"
#include "jsonvalidation_tests.c"

#define PRINTBYTES_TEST "HEY THERE GUYS LOOK AT ME"


int main(int argc, char* argv[])
{
//	printBytes(strlen(PRINTBYTES_TEST), PRINTBYTES_TEST, stdout, 8);

	jsonvalidation_runTests(1);
	getc(stdin);
	return 0;
}
