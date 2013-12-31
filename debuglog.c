#include "debuglog.h"

void printBytes(int length, void *data, FILE *output, int tabEvery, int bytesPerLine)
{
	int lines = (length / bytesPerLine) + 1;
	int i, j;
	int currentByte = 0;
	char *charString = (char *)malloc(sizeof(char) * bytesPerLine);
	char *byteString = (char *)malloc(sizeof(char) * bytesPerLine * 8 + sizeof(char) * (bytesPerLine));

	if(length == 0)
	{
		fprintf(output, "Data of length 0 given to printBytes\n");
		return;
	}

	for(i = 0; i < lines; i++)
	{
		for(j = 0; j < bytesPerLine; j++)
		{
			if(currentByte + j > length)
				*(charString + j) = ' ';
			else
				*(charString + j) = *(data + currentByte + j);
		}
		for(j = 0; j < bytesPerLine; j++)
		{
			if(currentByte + j > length)
				strcat((byteString + (j * (bytesPerLine + 1))), "         ");
			else
			{
				if(tabEvery != 0 && (j + 1) % tabEvery == 0)
					sprintf((byteString + (j * (bytesPerLine + 1))), "%08x\t", *(data + currentByte + j));
				else
					sprintf((byteString + (j * (bytesPerLine + 1))), "%08x ", *(data + currentByte + j));
			}
		}
		fprintf(output, "%p	%s	%s\n", (data + currentByte), byteString, charString);
		strcpy(charString, "");
		strcpy(byteString, "");
		currentByte += bytesPerLine;
	}

	free(charString);
	free(byteString);
	return;
}
