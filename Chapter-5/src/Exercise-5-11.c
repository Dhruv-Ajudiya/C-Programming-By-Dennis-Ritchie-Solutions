/*
 * This program replaces strings of blanks by the minimum number of
 * tabs and blanks to achieve the same spacing.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** MACRO DEFINITIONS */
#define TAB		8	/* Default tab size */
#define MAXLINE		100	/* Maximum line length */

/** FUNCTION PROTOTYPES */
void entab(char *strInput, char *strOutput, int iTabSize);
void detab(char *strInput, char *strOutput, int iTabSize);

/** MAIN PROGRAM */
/*
 * main: Reads a line of input from the user and processes it using
 *	 the specified mode ('en' for entab, 'de' for detab). Outputs
 *	 the resulting line.
 */
int main(int argc, char **argv)
{
	int iTabSize = TAB;	/* Number of spaces per tab */
	char strInput[MAXLINE];	/* Input line buffer */
	char strOutput[MAXLINE];/* Output line buffer */
	int iIndex = 0;		/* Index for iterating over input */
	int c;			/* Current input character */

	/* Check for the required number of arguments */
	if (argc < 2) {
		printf("Usage: %s <mode> [tab stop size]\n", argv[0]);
		return 0;
	}

	/* Validate mode */
	if (strcmp(argv[1], "en") != 0 && strcmp(argv[1], "de") != 0) {
		printf("Invalid mode specified. Use 'en' or 'de'.\n");
		return 0;
	}

	/* Update tab size if provided */
	if (argc == 3) {
		iTabSize = atoi(argv[2]);
	}

	/* Read input line */
	while ((c = getchar()) != '\n' && iIndex < MAXLINE - 1) {
		strInput[iIndex++] = c;
	}
	strInput[iIndex] = '\0'; /* Null-terminate the input string */

	/* Process input based on mode */
	if (strcmp(argv[1], "de") == 0) {
		detab(strInput, strOutput, iTabSize);
	} else {
		entab(strInput, strOutput, iTabSize);
	}

	/* Output the result */
	printf("%s\n", strOutput);

	return 0;
} /* End main() */

/*
 * detab	: Replaces tabs in the input string with the appropriate number
 *		  of spaces based on the tab size.
 * Input	: strInput (pointer to the input string),
 *		  strOutput (pointer to the output string),
 *		  iTabSize (number of spaces per tab stop).
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void detab(char *strInput, char *strOutput, int iTabSize)
{
	int iIndex = 0;	/* Index for output string */
	while (*strInput != '\0') {
		if (*strInput == '\t') {
			/* Replace tab with spaces */
			for (int i = 0; i < iTabSize; i++) {
				strOutput[iIndex++] = ' ';
			}
		} else {
			strOutput[iIndex++] = *strInput;
		}
		strInput++;
	}
	strOutput[iIndex] = '\0'; /* Null-terminate the output string */
} /* End detab() */

/*
 * entab	: Replaces sequences of spaces in the input string with the
 *		  minimum number of tabs and spaces.
 * Input	: strInput (pointer to the input string),
 *		  strOutput (pointer to the output string),
 *		  iTabSize (number of spaces per tab stop).
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void entab(char *strInput, char *strOutput, int iTabSize)
{
	int iIndex = 0;		/* Index for output string */
	int iBlanks = 0;	/* Count consecutive spaces */

	while (*strInput != '\0') {
		if (*strInput == ' ') {
			/* Count spaces */
			iBlanks++;
			while (*++strInput == ' ') {
				iBlanks++;
			}

			/* Replace spaces with tabs and remaining spaces */
			while (iBlanks >= iTabSize) {
				strOutput[iIndex++] = '\t';
				iBlanks -= iTabSize;
			}
			while (iBlanks > 0) {
				strOutput[iIndex++] = ' ';
				iBlanks--;
			}
		} else {
			/* Copy non-space characters */
			strOutput[iIndex++] = *strInput++;
		}
	}
	strOutput[iIndex] = '\0'; /* Null-terminate the output string */
} /* End entab() */
