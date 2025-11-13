/*
 * This program converts an uppercase string to its lowercase equivalent using
 * a conditional expression.
 * Author       : Dhruv Ajudiya
 * Created      : 16 August 2024
 * Modified     : 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MACRO DEFINITIONS */
#define MAXINPUT	100	/* Maximum length of input string */

/** FUNCTION PROTOTYPE */
void lowerString(char cInputString[]);

/** MAIN PROGRAM */
/*
 * main: It takes input from user and calls lowerString() function to convert uppercase
 *	 string to lowercase string.
 */
int main(void)
{
	char cInput[MAXINPUT];	/* Store input string from user */

	printf("Enter a string: ");
	fgets(cInput, sizeof(cInput), stdin);
	lowerString(cInput);
	printf("\nString in lowercase is: %s\n", cInput);

	return 0;
} /* End main() */

/*
 * lowerString	: Converts an uppercase string to a lowercase string using a conditional expression.
 * Input	: cInputString (input string to be converted)
 * Author       : Dhruv Ajudiya
 * Created      : 16 August 2024
 * Modified     : 16 August 2024
 */
void lowerString(char cInputString[])
{
	int i = 0; /* Index variable to iterate in loop */

	while (cInputString[i] != '\0') {
		cInputString[i] = (cInputString[i] >= 'A' && cInputString[i] <= 'Z') ?
					(cInputString[i] + 'a' - 'A') : (cInputString[i]);
		i++;
	}
} /* End lower() */
