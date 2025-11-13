/*
 * This program reads lines of text from the user, stores them, and sorts them.
 * Author	: Dhruv Ajudiya
 * Created	: 27 October 2024
 * Modified	: 27 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>

/** MACRO DEFINITIONS */
#define MAXLINES	5000	/* Maximum number of lines to be sorted */
#define MAXLEN		1000	/* Maximum length of any input line */
#define MAXBUFFSIZE	5000	/* Buffer size for storing lines */

/** GLOBAL VARIABLES */
char *cLineArray[MAXLINES];	/* Array of pointers to store each line */

/** FUNCTION PROTOTYPES */
int getLine(char *cLine, int iLimit);
int readLines(char *cLineArray[], char *cBuffer, int iMaxLines);
void writeLines(char *cLineArray[], int iNumLines);
void quickSort(char *cLineArray[], int iLeft, int iRight);

/** MAIN PROGRAM */
/*
 * main: Reads, sorts, and prints lines of text.
 */
int main(void)
{
	char cBuffer[MAXBUFFSIZE];	/* Buffer to hold all lines */
	int iNumLines;			/* Number of lines read */

	if ((iNumLines = readLines(cLineArray, cBuffer, MAXLINES)) >= 0) {
		quickSort(cLineArray, 0, iNumLines - 1);
		printf("\nSorted Lines:\n");
		writeLines(cLineArray, iNumLines);
		return 0;
	} else {
		printf("Error: Input too big to sort\n");
		return 1;
	}
} /* End main() */

/*
 * readLines	: Reads input lines and stores them in buffer.
 * Input	: cLineArray (array to hold pointers to each line)
 *		  cBuffer (buffer to store the lines)
 *		  iMaxLines (maximum lines allowed)
 * Return	: Number of lines read, or -1 if input exceeds limits
 * Author	: Dhruv Ajudiya
 * Created	: 27 October 2024
 * Modified	: 27 October 2024
 */
int readLines(char *cLineArray[], char *cBuffer, int iMaxLines)
{
	int iLineLen;			/* Length of the current line */
	int iNumLines = 0;		/* Counter for the number of lines read */
	char *cCurrentPos = cBuffer;	/* Pointer to the current position in buffer */
	char cLine[MAXLEN];		/* Array to hold each input line temporarily */

	/* Read lines until reaching EOF or exceeding the maximum line count */
	while ((iLineLen = getLine(cLine, MAXLEN)) > 0) {
		if (iNumLines >= iMaxLines || (MAXBUFFSIZE - (cCurrentPos - cBuffer)) < iLineLen)
			return -1;
		else {
			strcpy(cCurrentPos, cLine);
			cLineArray[iNumLines++] = cCurrentPos;
			cCurrentPos += iLineLen;
			*(cCurrentPos - 1) = '\0';
		}
	}
	return iNumLines;
} /* End readLines() */

/*
 * writeLines	: Prints all lines stored in buffer
 * Input	: cLineArray (array holding pointers to each line)
 *		  iNumLines (number of lines to print)
 * Author	: Dhruv Ajudiya
 * Created	: 27 October 2024
 * Modified	: 27 October 2024
 */
void writeLines(char *cLineArray[], int iNumLines)
{
	int i;	/* Index variable to iterate in loop */

	for (i = 0; i < iNumLines; i++)
		printf("%s\n", cLineArray[i]);
} /* End writeLines() */

/*
 * getLine	: Reads a line from standard input.
 * Input	: cLine (array to hold the line)
 *		  iLimit (maximum length of line)
 * Return 	: Length of the line read
 * Author	: Dhruv Ajudiya
 * Created	: 27 October 2024
 * Modified	: 27 October 2024
 */
int getLine(char *cLine, int iLimit)
{
	int iInputChar;		/* Character currently read */
	char *cStart = cLine;	/* Pointer to the start of the line buffer */

	/* Read characters until limit is reached, newline, or EOF */
	while (--iLimit > 0 && (iInputChar = getchar()) != EOF && iInputChar != '\n')
		*cLine++ = iInputChar;
	if (iInputChar == '\n')
		*cLine++ = iInputChar;
	*cLine = '\0';

	return cLine - cStart;
} /* End getLine() */

/*
 * quickSort	: Sorts an array of strings in ascending order.
 * Input	: cLineArray (array of pointers to lines)
 *		  iLeft (start index for sorting)
 *		  iRight (end index for sorting)
 * Author	: Dhruv Ajudiya
 * Created	: 27 October 2024
 * Modified	: 27 October 2024
 */
void quickSort(char *cLineArray[], int iLeft, int iRight)
{
	int i, iLast;		/* Index variable for partitioning */
	void swap(char *cLineArray[], int i, int j);

	if (iLeft >= iRight)	/* Return if less than two elements */
		return ;

	swap(cLineArray, iLeft, (iLeft + iRight) / 2);	/* Move pivot element to start */

	iLast = iLeft;
	for (i = iLeft + 1; i <= iRight; i++)	/* Partition around pivot */
		if (strcmp(cLineArray[i], cLineArray[iLeft]) < 0)
			swap(cLineArray, ++iLast, i);

	swap(cLineArray, iLeft, iLast);			/* Restore pivot element */
	quickSort(cLineArray, iLeft, iLast - 1); 	/* Sort left part */
	quickSort(cLineArray, iLast + 1, iRight); 	/* Sort right part */
} /* End quickSort() */

/*
 * swap		: Swaps two elements in an array.
 * Input	: pLineArray (array of pointers)
 *		  i (index of first element to swap)
 *		  j (index of second element to swap)
 * Author	: Dhruv Ajudiya
 * Created	: 27 October 2024
 * Modified	: 27 October 2024
 */
void swap(char *cLineArray[], int i, int j)
{
	char *cTemp = cLineArray[i];	/* Temporary pointer to hold line during swap */

	cLineArray[i] = cLineArray[j];
	cLineArray[j] = cTemp;
} /* End swap() */
