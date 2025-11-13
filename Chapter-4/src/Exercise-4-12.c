/*
 * This program demonstrates a recursive version of the itoa function,
 * which converts an integer to a string representation.
 * Author	: Dhruv Ajudiya
 * Created	: 29 August 2024
 * Modified	: 29 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>

/** MACRO DEFINITIONS */
#define MAXSIZE	100	/* Maximum size for the string buffer */

/** FUNCTION PROTOTYPES */
void itoa(int iNum, char cStr[]);

/** MAIN PROGRAM */
/*
 * main: It takes the input number from user, converts it to a string
 *	 using the itoa() function, and prints the result.
 */
int main(void)
{
	char cInputStr[MAXSIZE];	/* Buffer to store the string representation of the integer */
	int iInputNum;		/* Store the user input integer */

	printf("Enter an integer: ");
	scanf("%d", &iInputNum);

	itoa(iInputNum, cInputStr);
	printf("Converted string: %s\n", cInputStr);

	return 0;
} /* End main() */

/*
 * itoa		: Recursively converts an integer to a string
 * Input	: iNum (The integer to convert)
 *		  cStr (The buffer to store the resulting string)
 * Output	: The string representation of the integer
 * Author	: Dhruv Ajudiya
 * Created	: 29 August 2024
 * Modified	: 29 August 2024
 */
void itoa(int iNum, char cStr[])
{
	static int iIndex; /* Track the position in the string */

	if (iNum / 10) {
		itoa(iNum / 10, cStr);
	} else {
		if (iNum < 0)
			cStr[iIndex++] = '-';
	}

	cStr[iIndex++] = abs(iNum) % 10 + '0';
	cStr[iIndex] = '\0';
} /* End itoa() */
