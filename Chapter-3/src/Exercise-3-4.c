/*
 * This program converts an integer to a string representation, handling
 * the largest negative number in two's complement representation.
 * Author	: Dhruv Ajudiya
 * Created	: 22 August 2024
 * Modified	: 22 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>
#include <limits.h>

/** MACRO DEFINITIONS */
#define ABS(x)		((x) > 0 ? (x) : -(x))	/* Compute absolute value */
#define MAXLENGTH	100			/* Maximum size of the array */

/** FUNCTION PROTOTYPES */
void reverseString(char cString[]);
void itoa(int iNumber, char cResultString[]);

/** MAIN PROGRAM */
/*
 * main: It takes an integer from the user and converts it to a string using
 *	 the itoa() function. It then prints the converted string.
 */
int main(void)
{
	long iNumber;			/* Store the input number */
	char cConvertedStr[MAXLENGTH];	/* Store the converted string */

	printf("Enter the integer: ");
	scanf("%ld", &iNumber);
	if (iNumber < INT_MIN || iNumber > INT_MAX) {
		printf("Error: Number is out of the range of a 32-bit signed int.\n");
		return 1;
	}

	itoa(iNumber, cConvertedStr);
	printf("Converted string is: %s\n", cConvertedStr);

	return 0;
} /* End main() */

/*
 * itoa		: Converts an integer to a string representation, including
 *		  handling the largest negative number in two's complement.
 * Input	: iNumber (integer to convert)
 *		  cResultString (array to store the converted string)
 * Output	: Converted string from integer
 * Author	: Dhruv Ajudiya
 * Created	: 22 August 2024
 * Modified	: 22 August 2024
 */
void itoa(int iNumber, char cResultString[])
{
	int i = 0;		/* Index for the string */
	int iSign = iNumber;	/* Store the sign of the number */

	do {
		cResultString[i] = ABS(iNumber % 10) + '0';
		i++;
	} while ((iNumber /= 10) != 0);

	if (iSign < 0)
		cResultString[i++] = '-';

	cResultString[i] = '\0';

	reverseString(cResultString);
} /* End itoa() */

/*
 * reverseString	: Reverses the given string
 * Input		: cString (array containing the string to reverse)
 * Output		: Reversed string
 * Author		: Dhruv Ajudiya
 * Created		: 22 August 2024
 * Modified		: 22 August 2024
 */
void reverseString(char cString[])
{
	int i, j;	/* Index variables to iterate in the loop */
	char cTempChar;	/* Temporary variable for swapping */

	for (i = 0, j = strlen(cString) - 1; i < j; i++, j--) {
		cTempChar = cString[i];
		cString[i] = cString[j];
		cString[j] = cTempChar;
	}
} /* End reverse() */
