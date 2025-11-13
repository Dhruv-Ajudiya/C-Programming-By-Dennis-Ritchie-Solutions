/*
 * This program expands shorthand notations like a-z in the input string into the
 * complete list (e.g., abc...xyz).
 * Author  : Dhruv Ajudiya
 * Created : 22 August 2024
 * Modified: 22 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <ctype.h>

/** MACRO DEFINITIONS */
#define MAXLENGTH	100	/* Maximum length of the array */

/** FUNCTION PROTOTYPES */
void expand(char cInputString[], char cExpandedString[]);

/** MAIN PROGRAM */
/*
 * main: It reads a shorthand notation from the user and expands it using
 *	 the expand() function, then prints the expanded string.
 */
int main(void)
{
	char cInputString[MAXLENGTH];		/* Store the input shorthand notation */
	char cExpandedString[MAXLENGTH];	/* Store the expanded string */
	int i = 0;				/* Index variable to iterate in loop */
	int iInputChar;				/* Store input character from user */

	printf("Enter a shorthand notation: ");
	while ((iInputChar = getchar()) != '\n' && i < MAXLENGTH - 1)
		cInputString[i++] = iInputChar;
	cInputString[i] = '\0';

	expand(cInputString, cExpandedString);
	printf("Expanded string: %s\n", cExpandedString);

	return 0;
} /* End main() */

/*
 * expand	: Expands shorthand notations like a-z in the input string into the
 *		  complete list
 * Input	: cInputString (string with shorthand notations)
 *		  cExpandedString (string where expanded characters are stored)
 * Output	: Expanded string
 * Author	: Dhruv Ajudiya
 * Created	: 22 August 2024
 * Modified	: 22 August 2024
 */
void expand(char cInputString[], char cExpandedString[])
{
	int i = 0, j = 0;		/* Index variables to iterate in loop */
	char cTempStart, cTempEnd;	/* Temporary variables for character processing */

	while ((cTempStart = cInputString[i++]) != '\0') {
		if (cInputString[i] == '-' && ((isdigit(cTempStart) && isdigit(cInputString[i + 1])) ||
			(isalpha(cTempStart) && isalpha(cInputString[i + 1]) &&
			((islower(cTempStart) && islower(cInputString[i + 1])) ||
			(isupper(cTempStart) && isupper(cInputString[i + 1])))))) {

			cTempEnd = cInputString[i + 1];
			i += 2; /* Skip '-' and the next character */

			/* Expand in forward or reverse order */
			if (cTempStart < cTempEnd) {
				while (cTempStart <= cTempEnd)
					cExpandedString[j++] = cTempStart++;
			} else {
				while (cTempStart >= cTempEnd)
					cExpandedString[j++] = cTempStart--;
			}

		} else {
			/* If not a valid range, just copy the characters */
			cExpandedString[j++] = cTempStart;
		}
	}

	cExpandedString[j] = '\0';
} /* End expand() */
