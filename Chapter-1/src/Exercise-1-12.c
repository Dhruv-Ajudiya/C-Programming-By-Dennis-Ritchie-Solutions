/*
 * This program takes input and outputs each word on a new line.
 * Author	: Dhruv Ajudiya
 * Created	: 13 August 2024
 * Modified	: 13 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MACRO DEFINITIONS */
#define IN	 1	/* Inside a word */
#define OUT	 0	/* Outside a word */

/** MAIN PROGRAM */
/*
 * main: Take the input and prints each word on new line.
 */
int main(void)
{
	int iInputChar;	/* Store the input character from the user */
	int iState;	/* Flag to check if it is inside a word */

	iState = OUT;	/* Not inside a word */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iInputChar = getchar()) != EOF) {
		if (iInputChar == ' ' || iInputChar == '\n' || iInputChar == '\t') {
			if (iState == IN) {
				putchar('\n');
				iState = OUT;
			}
		} else {
			putchar(iInputChar);
			iState = IN;
		}
	}

	return 0;
} /* End main() */
