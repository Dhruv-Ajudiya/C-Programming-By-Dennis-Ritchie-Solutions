/*
 * This program reverses the character string using user-defined function.
 * Author	: Dhruv Ajudiya
 * Created	: 14 August 2024
 * Modified	: 14 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACRO */
#define MAXLINE		1000	/* Maximum input line length */

/** FUNCTION PROTOTYPES */
int getLine(char cLine[], int iMaxLen);
void reverseString(char cLine[]);

/** MAIN PROGRAM */
/*
 * main: It calls getLine() function to take input character from user and store the
 *	 string in an array and calls reverseString() to reverse the string.
 */
int main(void)
{
	int iLen;		/* Current line length */
	char cLine[MAXLINE];	/* Current input line */

	printf("Enter the string to reverse (Press Ctrl+D to end input):\n");
	while ((iLen = getLine(cLine, MAXLINE)) > 0) {
		reverseString(cLine);
		printf("Reversed string: %s\n", cLine);
		printf("Enter another string to reverse (Press Ctrl+D to end input):\n");
	}

	return 0;
} /* End main() */

/*
 * getLine	: Reads a line from the console
 * Input	: cLine (character array to store the input line)
 *		  iMaxLen (maximum length of the line that can be stored)
 * Return	: Length of the input line
 * Author	: Dhruv Ajudiya
 * Created	: 14 August 2024
 * Modified	: 14 August 2024
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
 * reverseString	: Reverses the given character string in place
 * Input		: cLine (character array containing the string to reverse)
 * Author		: Dhruv Ajudiya
 * Created		: 14 August 2024
 * Modified		: 14 August 2024
 */
void reverseString(char cLine[])
{
	int i;			/* Index variable to iterate in the loop */
	int iLength = 0;	/* Store the length of the string */
	char cTemp;		/* Temporary variable for swapping characters */

	for (i = 0; cLine[i] != '\n'; i++)
		iLength++;

	i = 0;
	while (i < iLength) {
		cTemp = cLine[i];
		cLine[i] = cLine[iLength];
		cLine[iLength] = cTemp;
		i++;
		iLength--;
	}
} /* End reverse() */
