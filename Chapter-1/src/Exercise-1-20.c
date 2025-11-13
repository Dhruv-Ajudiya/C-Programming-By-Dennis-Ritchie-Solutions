/*
 * This program replaces tabs in the input with the proper number of blanks to
 * space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACRO */
#define MAXLINE		100	/* Maximum input line length */
#define TABSTOP		8	/* Tab space on the machine */

/** FUNCTION PROTOTYPES */
int getLine(char cLine[], int iMaxLen);
void detab(char cDestination[], char cSource[]);

/** MAIN PROGRAM */
/*
 * main: It takes input from user using getLine() function and replaces tabs
 *	 in the input with proper number of blanks using detab() function.
 */
int main(void)
{
	int iLen;			/* Current line length */
	char cLine[MAXLINE];		/* Current input line */
	char cDetabbedLine[MAXLINE];	/* Line after detabbing */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iLen = getLine(cLine, MAXLINE)) > 0) {
		detab(cDetabbedLine, cLine);
		printf("Line after detabbing:\n%s", cDetabbedLine);
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
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */
int getLine(char cLine[], int iMaxLen)
{
	int iInputChar;	/* Store the input character from user */
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

/*
 * detab	: Replaces tabs in the input with the proper number of blanks
 * Input	: cDestination (output line with tabs replaced)
 *		  cSource (input line)
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */
void detab(char cDestination[], char cSource[])
{
	int iSourceIndex;	/* Index variable for source string */
	int iDestIndex = 0;	/* Index variable for destination string */
	int iNumOfBlanks;	/* Number of blanks to replace the tab */
	int j;			/* Index varaible to iterate in loop */

	for (iSourceIndex = 0; cSource[iSourceIndex] != '\0'; iSourceIndex++) {
		if (cSource[iSourceIndex] == '\t') {
			iNumOfBlanks = TABSTOP - (iDestIndex % TABSTOP);
			for (j = 0; j < iNumOfBlanks; j++) {
				cDestination[iDestIndex] = ' ';
				iDestIndex++;
			}
		} else {
			cDestination[iDestIndex] = cSource[iSourceIndex];
			iDestIndex++;
		}
	}

	cDestination[iDestIndex] = '\0';
} /* End detab() */
