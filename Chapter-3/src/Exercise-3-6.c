/*
 * This program converts integer to a string representation with a specified
 * minimum field width. The converted number is padded with blanks on the left
 * if necessary to meet the width requirement.
 * Author	: Dhruv Ajudiya
 * Created	: 22 August 2024
 * Modified	: 22 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>

/** REQUIRED MACRO */
#define MAXLENGTH	100	/* Maximum length of the array */

/** FUNCTION PROTOTYPES */
void reverseString(char cString[]);
void itoa(int iNumber, char cResultString[], int iWidth);

/** MAIN PROGRAM */
/*
 * main: It takes an integer and a field width from the user and converts the
 *	 integer to a string using the itoa() function with the specified width.
 *	 It also prints the converted string.
 */
int main(void)
{
	int iNumber;			/* Store the input number */
	int iWidth;			/* Store the minimum field width */
	char cConvertedStr[MAXLENGTH];	/* Store the converted string */

	printf("Enter the integer: ");
	scanf("%d", &iNumber);
	printf("Enter the field width: ");
	scanf("%d", &iWidth);

	itoa(iNumber, cConvertedStr, iWidth);
	printf("Converted string is: %s\n", cConvertedStr);

	return 0;
} /* End main() */

/*
 * itoa		: Converts an integer to a string representation with a specified
 *		  minimum field width, padding with blanks on the left if necessary.
 * Input	: iNumber (integer to convert)
 *		  cResultString (array to store the converted string)
 *		  iWidth (minimum field width)
 * Output	: Converted string from integer with minimum field width
 * Author	: Dhruv Ajudiya
 * Created	: 22 August 2024
 * Modified	: 22 August 2024
 */
void itoa(int iNumber, char cResultString[], int iWidth)
{
	int i = 0;		/* Index for the string */
	int iSign = iNumber;	/* Store the sign of the number */

	if (iNumber < 0)
		iNumber = -iNumber;

	do {
		cResultString[i] = (iNumber % 10) + '0';
		i++;
	} while ((iNumber /= 10) > 0);

	if (iSign < 0)
		cResultString[i++] = '-';

	while (i < iWidth)
		cResultString[i++] = ' ';

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
