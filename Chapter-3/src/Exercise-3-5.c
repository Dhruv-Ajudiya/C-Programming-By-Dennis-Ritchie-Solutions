/*
 * This program converts integer into a string representation in a specified
 * base. The itob() function handles conversions to various bases including
 * hexadecimal, binary, etc.
 * Author	: Dhruv Ajudiya
 * Created	: 22 August 2024
 * Modified	: 22 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>
#include "error_handling.h"

/** MACRO DEFINITIONS */
#define MAXLENGTH	100	/* Maximum size of the array */

/** FUNCTION PROTOTYPES */
void reverseString(char cString[]);
void itob(int iNumber, char cResultString[], int iBase);

/** MAIN PROGRAM */
/*
 * main: It takes integer and a base from the user and converts the integer
 *	 to a string in the specified base using the itob() function. It also
 *	 prints the converted string.
 */
int main(void)
{
	int iNumber;			/* Store the input number */
	int iBase;			/* Store the base for conversion */
	char cConvertedStr[MAXLENGTH];	/* Store the converted string */

	printf("Enter the integer: ");
	scanf("%d", &iNumber);
	printf("Enter the base: ");
	scanf("%d", &iBase);

	if (iBase <= 0)
		handleError(ERROR_INVALID_INPUT);

	itob(iNumber, cConvertedStr, iBase);
	printf("Converted string is: %s\n", cConvertedStr);

	return 0;
} /* End main() */

/*
 * itob		: Converts integer to a string representation in a specified base
 * Input	: iNumber (integer to convert)
 *		  cResultString (array to store the converted string)
 *		  iBase (base for conversion)
 * Output	: Converted string from integer in the specified base
 * Author	: Dhruv Ajudiya
 * Created	: 22 August 2024
 * Modified	: 22 August 2024
 */
void itob(int iNumber, char cResultString[], int iBase)
{
	int i = 0;		/* Index variable to iterate in the loop */
	int iSign = iNumber;	/* Store the sign of the number */
	int iRemainder;		/* Store the remainder for conversion */

	if (iSign < 0)
		iNumber = -iNumber;

	do {
		iRemainder = iNumber % iBase;
		cResultString[i] = (iRemainder < 10) ? iRemainder + '0' : iRemainder + 'A' - 10;
		i++;
	} while ((iNumber /= iBase) > 0);

	if (iSign < 0)
		cResultString[i++] = '-';

	cResultString[i] = '\0';

	reverseString(cResultString);
} /* End itob() */

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
