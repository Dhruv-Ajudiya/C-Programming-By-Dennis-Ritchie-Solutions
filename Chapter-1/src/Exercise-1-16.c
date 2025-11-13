/*
 * This program correctly prints the length of arbitrary long input lines, and
 * as much as possible of the text in its input.
 * Author	: Dhruv Ajudiya
 * Created	: 13 August 2024
 * Modified	: 13 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACRO */
#define MAXLINE 100 /* Maximum input line length */

/** FUNCTION PROTOTYPES */
int getLine(char cLine[], int iMaxLen);
void copyString(char cDestination[], char cSource[]);

/** MAIN PROGRAM */
/*
 * main: It calls getLine() function to take input from the user and correctly
 *	 print the length of arbitrary long input lines, and as much as possible of
 *	 the text.
 */
int main(void)
{
	int iLen;		/* Current line length */
	int iMax;		/* Maximum length seen so far */
	int iInputChar;		/* Store the input character from user */
	char cLine[MAXLINE];	/* Current input line */
	char cLongest[MAXLINE];	/* Longest line saved */

	iMax = 0;
	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iLen = getLine(cLine, MAXLINE)) > 0) {
		if (cLine[iLen - 1] != '\n') { /* Second last element */
			while ((iInputChar = getchar()) != '\n')
				iLen++;
			iLen++; /* Newline character */
		}
		if (iLen > iMax) {
			iMax = iLen;
			copyString(cLongest, cLine);
		}
		printf("Enter the string (Press Ctrl+D to end input):\n");
	}

	if (iMax > 0) { /* There was at least one line */
		printf("\nLength of the longest line is: %d\n", iMax);
		printf("Longest line text: %s\n", cLongest);
	}

	return 0;
} /* End main() */

/*
 * getLine	: Reads a line from the console
 * Input	: cLine (character array to store the input line)
 *		  iMaxLen (maximum length of the line that can be stored)
 * Return	: Length of the input line
 * Author	: Dhruv Ajudiya
 * Created	: 13 August 2024
 * Modified	: 13 August 2024
 */
int getLine(char cLine[], int iMaxLen)
{
	int iInputChar; /* Store the input character from user */
	int i; /* Index variable to iterate in the loop */

	for (i = 0; i < iMaxLen - 1 && (iInputChar = getchar()) != EOF && iInputChar != '\n'; i++)
		cLine[i] = iInputChar;

	if (iInputChar == '\n') {
		cLine[i] = iInputChar;
		i++;
	}
	cLine[i] = '\0';

	return i; /* Length of the string */
} /* End getLine() */

/*
 * copyString	: Copies the content of source array into destination array
 * Input	: cDestination (array where the content will be copied)
 *		  cSource (array to copy from)
 * Author	: Dhruv Ajudiya
 * Created	: 13 August 2024
 * Modified	: 13 August 2024
 */
void copyString(char cDestination[], char cSource[])
{
	int i = 0; /* Index variable to iterate in loop */

	while ((cDestination[i] = cSource[i]) != '\0')
		++i;
} /* End copy() */
