/*
 * This program counts the number of blank spaces, tabs and newline.
 * Author	: Dhruv Ajudiya
 * Created	: 12 August 2024
 * Modified	: 12 August 2024
 */

/* REQUIRED HEADER FILES */
#include <stdio.h>

/** MAIN PROGRAM */
/*
 * main: Count the number of blank spaces, tabs and newline.
 */
int main(void)
{
	int iInputChar;	/* Store the input character from the user */
	int iBlanks;	/* Number of blank spaces */
	int iNewLine;	/* Number of newlines */
	int iTabs;	/* Number of tabs */

	iBlanks = iNewLine = iTabs = 0;
	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iInputChar = getchar()) != EOF) {
		if (iInputChar == ' ')
			iBlanks++;
		if (iInputChar == '\n')
			iNewLine++;
		if (iInputChar == '\t')
			iTabs++;
	}

	printf("\nNo. of Blanks: %d\nNo. of Newline: %d\nNo. of Tabs: %d\n", iBlanks, iNewLine, iTabs);

	return 0;
} /* End main() */
