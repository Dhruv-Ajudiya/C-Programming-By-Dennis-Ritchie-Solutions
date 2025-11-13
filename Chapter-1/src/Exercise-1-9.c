/*
 * This program copies the input to its output, replacing each string of one or
 * more blank spaces by a single blank space.
 * Author	: Dhruv Ajudiya
 * Created	: 12 August 2024
 * Modified	: 12 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MAIN PROGRAM */
/*
 * main: Copies the input to its output, replacing each string of one or more
 *	 blank spaces by a single blank space.
 */
int main(void)
{
	int iInputChar; /* Store the input character from the user */
	int iBlankFlag; /* Flag to moniter the spaces */

	iBlankFlag = 0; /* Indicates that no blank spaces occurred */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iInputChar = getchar()) != EOF) {
		if (iInputChar == ' ') {
			if (!iBlankFlag) {
				putchar(iInputChar);
				iBlankFlag = 1;
			}
		} else {
			putchar(iInputChar);
			iBlankFlag = 0;
		}
	}

	return 0;
} /* End main() */
