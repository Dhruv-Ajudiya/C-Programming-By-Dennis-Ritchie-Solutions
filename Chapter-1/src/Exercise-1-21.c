/*
 * This program replaces replaces strings of blanks by the minimum number of
 * tabs and blanks to achieve the same spacing.
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
void entab(char cDestination[], char cSource[]);

/** MAIN PROGRAM */
/*
 * main: Takes input line from user using getLine() function and replaces strings
 *	 of blanks by the minimum number of tabs and blanks to achieve the same spacing.
 */
int main(void)
{
	int iLen;			/* Current line length */
	char cLine[MAXLINE];		/* Current input line */
	char cEntabbedLine[MAXLINE];	/* Line after entabbing */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iLen = getLine(cLine, MAXLINE)) > 0) {
		entab(cEntabbedLine, cLine);
		printf("Line after entabbing:\n%s", cEntabbedLine);
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
 * entab	: Replaces tabs in the input with the proper number of blanks
 * Input	: cDestination (output line with tabs replaced)
 *		  cSource (input line)
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */
void entab(char cDestination[], char cSource[])
{
	int iNumSpaces = 0;	/* Count of spaces */
	int iNumTabs = 0;	/* Count of tabs */
	int iPosition = 1;	/* Current column position */
	int iSourceIndex;	/* Index variable for source string */
	int iDestIndex = 0;	/* Index variable for destination string */
	int j;			/* Index varaible to iterate in loop */

	for (iSourceIndex = 0; cSource[iSourceIndex] != '\0'; iSourceIndex++) {
		if (cSource[iSourceIndex] == ' ') {
			if (iPosition % TABSTOP != 0) {
				iNumSpaces++;
			} else {
				iNumSpaces = 0;
				iNumTabs++;
			}
		} else {
			/* Insert tabs */
			for (j = 0; j < iNumTabs; j++)
				cDestination[iDestIndex++] = '\t';
			iNumTabs = 0;

			if (cSource[iSourceIndex] == '\t') {
				iNumSpaces = 0;
				iPosition = iPosition + (TABSTOP - (iPosition - 1) % TABSTOP) - 1;
			}

			/* Insert spaces */
			for (j = 0; j < iNumSpaces; j++)
				cDestination[iDestIndex++] = ' ';
			iNumSpaces = 0;

			cDestination[iDestIndex] = cSource[iSourceIndex];
			iDestIndex++;

			if (cSource[iSourceIndex] == '\n')
				iPosition = 0;
		}
		iPosition++;
	}

	cDestination[iDestIndex] = '\0';
} /* End entab() */
