#include "printutils.h"

#define BYTES_PER_32 4

void printBytes(int length, void *data, FILE *output, int bytesPerLine)
{
	int lines = length % bytesPerLine == 0 ? (length/bytesPerLine) : (length / bytesPerLine) + 1;
	int i, j;
	int currentByte = 0;
	char *charString = (char *)malloc(sizeof(char) * bytesPerLine + sizeof(char));
	char *byteString = (char *)malloc(sizeof(char) * bytesPerLine * 2 + sizeof(char) * (bytesPerLine) + sizeof(char));

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
				*(charString + j) = *((char *)data + currentByte + j);
		}
		//Null terminate
		*(charString + j) = 0;

		//Assemble Bytes
		for(j = 0; j < bytesPerLine; j++)
		{
			if(currentByte + j >= length)
			{
				if((j + 1) % BYTES_PER_32 == 0)
					strcat((byteString + (j * 2) + (j/BYTES_PER_32) - 1), "   ");
				else if(j % BYTES_PER_32 == 0 && j != 0)
					strcat((byteString + (j * 2) +  (j/BYTES_PER_32)), "  ");
				else
					strcat((byteString + (j * 2) + (j/BYTES_PER_32)), "  ");
			}
			else
			{
				//Put a space between each 4-byte group
				if((j + 1) % BYTES_PER_32 == 0)
					sprintf((byteString + (j * 2) + (j/BYTES_PER_32)), "%02x ", *((char *)data + currentByte + j));
				//Need a different pointer addition for adding the space
				else if(j % BYTES_PER_32 == 0 && j != 0)
					sprintf((byteString + (j * 2) + (j/BYTES_PER_32)), "%02x", *((char *)data + currentByte + j));
				else
					sprintf((byteString + (j * 2) + (j/BYTES_PER_32)), "%02x", *((char *)data + currentByte + j));
			}
		}
		//Null Terminate
		*(byteString + (j-1) * (bytesPerLine) + (j/BYTES_PER_32) + 1) = 0;
		fprintf(output, "0x%p	%s	%s\n", ((char *)data + currentByte), byteString, charString);
		strcpy(charString, "");
		strcpy(byteString, "");
		currentByte += bytesPerLine;
	}

	free(charString);
	free(byteString);
	return;
}
