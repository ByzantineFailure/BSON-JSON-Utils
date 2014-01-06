#ifndef STD_INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STD_INCLUDES
#endif

#define BYTES_PER_LINE 4

void printBytes(int length, void *data, FILE *output, int bytesPerLine);