/*
 * This program writes a loop equivalent to the for loop without using && or ||
 * for the getLine() function.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MACRO DEFINITIONS */
#define MAXLINE		10	/* Maximum input line length */

/** FUNCTION PROTOTYPES */
int getLine(char cLine[], int iMaxLen);

/** MAIN PROGRAM */
/*
 * main: It calls getLine() function to take input from the user and prints on the console.
 */
int main(void)
{
	char cLine[MAXLINE]; /* Store the input from the user */

	printf("Enter the string: ");
	getLine(cLine, MAXLINE);
	printf("\nEntered string is: %s\n", cLine);

	return 0;
} /* End main() */

/*
 * getLine	: Reads a line from the console
 * Input	: cLine (character array to store the input line)
 *		  iMaxLen (maximum length of the line that can be stored)
 * Return	: Length of the input line
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */
int getLine(char cLine[], int iMaxLen)
{
	int iInputChar;	/* Store the input character from user */
	int i = 0;	/* Index variable to iterate in the loop */

	while (i < iMaxLen - 1) {
		iInputChar = getchar();

		if (iInputChar == EOF)
			break;
		if (iInputChar == '\n')
			break;
		cLine[i] = iInputChar;
		i++;
	}

	if (iInputChar == '\n') {
		cLine[i] = iInputChar;
		i++;
	}
	cLine[i] = '\0';

	return i; /* Length of the string */
} /* End getLine() */
