/*
 * This Program folds long input lines into shorter lines after the last non-blank
 * character that occurs before the n-th column of input.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACROS */
#define COLUMN_WIDTH	10	/* Maximum number of columns before folding */
#define MAX_BUFFER	1000	/* Maximum buffer size */
#define TABSTOP		8	/* Tabstop size of the machine */

/** MAIN PROGRAM */
/*
 * main: Folds long input lines into shorter lines at the last non-blank character
 *	 before the specified column width.
 */
int main(void)
{
	int iInputChar;			/* Current input character */
	int iBufferIndex = 0;		/* Index for buffer array */
	int iPosition = 1;		/* Current column position */
	int iTabFactor;			/* Factor to determine tab stops */
	char cBuffer[MAX_BUFFER];	/* Buffer array to store characters */

	printf("Enter the input (Press Ctrl+D to end):\n");
	while ((iInputChar = getchar()) != EOF) {
		cBuffer[iBufferIndex] = iInputChar;
		iBufferIndex++;

		/* Handle buffer overflow */
		if (iBufferIndex == MAX_BUFFER - 1) {
			cBuffer[iBufferIndex] = '\0';
			printf("%s", cBuffer);
			iBufferIndex = 0;
		}

		if (iInputChar == '\n') {
			iPosition = 1;
		} else if (iInputChar == '\t') {
			/* Calculate the new column position after a tab */
			iTabFactor = (iPosition - 1) / TABSTOP + 1;
			iPosition = iTabFactor * TABSTOP + 1;
		} else {
			iPosition++;
		}

		if (iPosition > COLUMN_WIDTH) {
			cBuffer[iBufferIndex] = '\n';
			iBufferIndex++;

			/* Handle buffer overflow */
			if (iBufferIndex == MAX_BUFFER - 1) {
				cBuffer[iBufferIndex] = '\0';
				printf("%s", cBuffer);
				iBufferIndex = 0;
			}
			iPosition = 1;

			/* Handle case where last character in a line falls at COLUMN_WIDTH */
			iInputChar = getchar();
			if (iInputChar != '\n') {
				cBuffer[iBufferIndex] = iInputChar;
				iBufferIndex++;
				iPosition++;
			}
		}

		/* Handle buffer overflow */
		if (iBufferIndex == MAX_BUFFER - 1) {
			cBuffer[iBufferIndex] = '\0';
			printf("%s", cBuffer);
			iBufferIndex = 0;
		}
	}

	cBuffer[iBufferIndex] = '\0';
	printf("%s", cBuffer);

	return 0;
} /* End main() */
