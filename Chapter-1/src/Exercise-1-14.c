/*
 * This program prints a histogram of the frequencies of different characters
 * in its input.
 * Author	: Dhruv Ajudiya
 * Created	: 13 August 2024
 * Modified	: 13 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACRO */
#define MAXCHAR 128 /* Maximum no of characters */

/** MAIN PROGRAM */
/*
 * main: Print a histogram of the frequencies of different characters
 *	 in its input.
 */
int main(void)
{
	int i, j;			/* Index variables to iterate over loop */
	int iInputChar;			/* Store the input character from user */
	int iFreq[MAXCHAR] = {0};	/* Store the frequency of characters occured */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iInputChar = getchar()) != EOF)
		iFreq[iInputChar]++;

	printf("\nHistogram of frequencies of different characters\n");
	for (i = 0; i < MAXCHAR; i++) {
		if (iFreq[i] > 0) {
			printf("%c: ", i);
			for (j = 0; j < iFreq[i]; j++)
				printf("*");
			printf("\n");
		}
	}

	return 0;
} /* End main() */
