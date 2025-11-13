/*
 * This program prints all input lines that are longer than 80 characters.
 * Author	: Dhruv Ajudiya
 * Created	: 14 August 2024
 * Modified	: 14 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACRO */
#define MAXLINE		100	/* Maximum input line length */
#define CHARLIMIT	8	/* Maximum words per line */

/** FUNCTION PROTOTYPES */
int getLine(char cLine[], int iMaxLen);

/** MAIN PROGRAM */
/*
 * main: It calls getLine() function to take input from the user and print all
 *	 input lines that are longer than 80 characters.
 */
int main(void)
{
	int iLen;		/* Current line length */
	char cLine[MAXLINE];	/* Current input line */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iLen = getLine(cLine, MAXLINE)) > 0) {
		if (iLen > CHARLIMIT)
			printf("\nLine longer than %d characters:\n%s\n", CHARLIMIT, cLine);

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
