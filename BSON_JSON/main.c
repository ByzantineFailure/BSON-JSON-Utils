#include "printutils.h"
#include "jsonutils.h"

#define PRINTBYTES_TEST "HEY THERE GUYS LOOK AT ME"

int main(int argc, char* argv[])
{
	printBytes(strlen(PRINTBYTES_TEST), PRINTBYTES_TEST, stdout, 8);

	fprintf(stdout, "%d", json_checkValidJSON("{\"Hi\": }"));
	getc(stdin);
}