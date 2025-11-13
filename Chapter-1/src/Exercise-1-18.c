/*
 * This program removes trailing blanks and tabs from each line of input, and
 * deletes entirely blank lines.
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

/** MAIN PROGRAM */
/*
 * main: It calls the getLine() function to take the input from the user and removes
 *	 the trailing blanks and tabs from each line and deletes entirely blank lines.
 */
int main(void)
{
	int iLen;		/* Current line length */
	char cLine[MAXLINE];	/* Current input line */
	int i; /* Index variable to iterate in the loop */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iLen = getLine(cLine, MAXLINE)) > 0) {
		i = iLen - 2;
		while (i >= 0 && (cLine[i] == ' ' || cLine[i] == '\t'))
			i--;

		if (i >= 0) {
			cLine[++i] = '\n';
			cLine[++i] = '\0';
			printf("String after removing trailing blank spaces and tabs:\n%s", cLine);
		} else {
			printf("Blank line\n");
		}
		printf("Enter the string (Press Ctrl+D to end input):\n");
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
