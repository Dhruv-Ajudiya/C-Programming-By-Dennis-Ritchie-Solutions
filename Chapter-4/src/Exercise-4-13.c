/*
 * This program demonstrates the use of a recursive function to reverse a string.
 * Author	: Dhruv Ajudiya
 * Created	: 29 August 2024
 * Modified	: 29 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>

/** MACRO DEFINITIONS */
#define MAXSIZE	100	/* Maximum size of the input array */

/** FUNCTION PROTOTYPES */
void reverseString(char cInputString[]);

/** MAIN PROGRAM */
/*
 * main: It takes the string as an input from user, prints it, calls the reverse function
 *	 to reverse the string, and then prints the reversed string.
 */
int main(void)
{
	char cInputString[MAXSIZE];	/* Array to store the input string */
	int iInputChar;			/* Store input character from user */
	int i = 0;			/* Index variable to iterate in loop */

	printf("Enter a string to reverse: ");
	while ((iInputChar = getchar()) != '\n')
		cInputString[i++] = iInputChar;
	cInputString[i] = '\0';

	reverseString(cInputString);
	printf("After reversing: %s\n", cInputString);

	return 0;
} /* End main() */

/*
 * reverseString	: Recursively reverses the given string
 * Input		: cInputString (the string to be reversed)
 * Output		: Reverses the input string
 * Author		: Dhruv Ajudiya
 * Created		: 29 August 2024
 * Modified		: 29 August 2024
 */
void reverseString(char cInputString[])
{
	static int iStrLength;	/* Length of the input string */
	static int iStartIndex;	/* Starting index for reversal */
	int iEndIndex;		/* Ending index for reversal */
	char cTempChar;		/* Temporary variable for swapping characters */

	if (iStartIndex == 0)
		iStrLength = strlen(cInputString);

	iEndIndex = iStrLength - (iStartIndex + 1);
	if (iStartIndex < iEndIndex) {
		cTempChar = cInputString[iStartIndex];
		cInputString[iStartIndex] = cInputString[iEndIndex];
		cInputString[iEndIndex] = cTempChar;
		iStartIndex++;
		reverseString(cInputString);
	} else {
		iStartIndex = 0; /* Reset index */
	}
} /* End reverseString() */
