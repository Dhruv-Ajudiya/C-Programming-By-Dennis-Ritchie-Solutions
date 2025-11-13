/*
 * This program count the number of lines, words and charcters.
 * Author	: Dhruv Ajudiya
 * Created	: 13 August 2024
 * Modified	: 13 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MACRO DEFINITIONS */
#define IN	1	/* Inside a word */
#define OUT	0	/* Outside a word */

/** MAIN PROGRAM */
/*
 * main: Count the number of lines, words and characters.
 */
int main(void)
{
	int iInputChar;	/* Store the input character from the user */
	int iNLines;	/* Number of lines */
	int iNWords;	/* Number of words */
	int iNChar;	/* Number of characters */
	int iState;	/* Flag to check if it is inside a word */

	iState = OUT;	/* Not inside a word */
	iNLines = iNWords = iNChar = 0;

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iInputChar = getchar()) != EOF) {
		++iNChar;
		if (iInputChar == '\n')
			++iNLines;
		if (iInputChar == ' ' || iInputChar == '\n' || iInputChar == '\t')
			iState = OUT;
		else if (iState == OUT) {
			iState = IN;
			++iNWords;
		}
	}
	printf("\nNo. of Lines: %d\nNo. of Words: %d\nNo. of Characters: %d\n", iNLines, iNWords, iNChar);

	return 0;
} /* End main() */
