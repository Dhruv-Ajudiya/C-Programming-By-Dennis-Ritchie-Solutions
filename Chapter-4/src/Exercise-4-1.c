/*
 * This program finds the position of the rightmost occurrence of a pattern in a line of text.
 * Author	: Dhruv Ajudiya
 * Created	: 23 August 2024
 * Modified	: 23 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <ctype.h>

/** MACRO DEFINITIONS */
#define MAXLENGTH	1000	/* Maximum input line length */

/** FUNCTION PROTOTYPES */
int getLine(char cLine[], int iMaxLen);
int strRightIndex(char cSourceString[], char cSearchString[]);

/** MAIN PROGRAM */
/*
 * main: It reads a pattern to search for and lines of text from the user, searches for the pattern
 *       in each line, and prints the lines where the pattern is found along with its position.
 */
int main(void)
{
	char cInputLine[MAXLENGTH];	/* Store the input line from the user */
	char cSearchString[MAXLENGTH];	/* The pattern to search for */
	int iRightIndex;		/* Index of the rightmost occurrence of the cSearchString */
	int i = 0;			/* Index variable to iterate in loop */
	int iInputChar;			/* Store the input character from user */

	printf("Enter the pattern to search for: ");
	while ((iInputChar = getchar()) != EOF && iInputChar != '\n')
		cSearchString[i++] = iInputChar;
	cSearchString[i] = '\0';

	printf("Enter the input line to search in (Press Ctrl + D to end input):\n");
	while (getLine(cInputLine, MAXLENGTH) > 0) {
		iRightIndex = strRightIndex(cInputLine, cSearchString);
		if (iRightIndex >= 0) {
			printf("Pattern found in: %s", cInputLine);
			printf("Rightmost occurrence at position: %d\n", iRightIndex);
		} else {
			printf("Pattern not found in: %s", cInputLine);
		}
	}

	return 0;
} /* End main() */

/*
 * strRightIndex	: Returns the position of the rightmost occurrence of pattern(cSearchString)
 *			  in input(cSourceString) string
 * Input		: cSourceString (the string to search in)
 *			  cSearchString (the pattern to search for)
 * Return		: Index of the rightmost occurrence of the pattern in string, or -1 if not found
 * Author		: Dhruv Ajudiya
 * Created		: 23 August 2024
 * Modified		: 23 August 2024
 */
int strRightIndex(char cSourceString[], char cSearchString[])
{
	int i, j, k;		/* Index variables to iterate in loop */
	int iRightIndex = -1;	/* Initialize the rightmost index to -1 (not found) */

	for (i = 0; cSourceString[i] != '\0'; i++) {
		for (j = i, k = 0; cSearchString[k] != '\0' && tolower(cSourceString[j])
				== tolower(cSearchString[k]); j++, k++)
			;

		if (k > 0 && cSearchString[k] == '\0')
			iRightIndex = i + 1;
	}

	return iRightIndex;
} /* End strRightIndex() */

/*
 * getLine	: Reads a line from the console
 * Input	: cLine (character array to store the input line)
 *		  iMaxLen (maximum length of the line that can be stored)
 * Return	: Length of the input line
 * Author	: Dhruv Ajudiya
 * Created	: 23 August 2024
 * Modified	: 23 August 2024
 */
int getLine(char cLine[], int iMaxLen)
{
	int iInputChar; /* Store the input character from user */
	int i;		/* Index variable to iterate in the loop */

	for (i = 0; i < iMaxLen - 1 && (iInputChar = getchar()) != EOF && iInputChar != '\n'; i++)
		cLine[i] = iInputChar;

	if (iInputChar == '\n') {
		cLine[i] = iInputChar;
		i++;
	}
	cLine[i] = '\0';

	return i; /* Length of the string */
} /* End getLine() */
