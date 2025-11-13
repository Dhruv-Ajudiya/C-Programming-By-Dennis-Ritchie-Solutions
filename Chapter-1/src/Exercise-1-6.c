/*
 * This program verifies that the vaule of the expression getchar() != EOF is 0 or 1.
 * Author	: Dhruv Ajudiya
 * Created	: 12 August 2024
 * Modified	: 12 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MAIN PROGRAM */
/*
 * main: Print the value of expression getchar() != EOF.
 */
int main(void)
{
	int iInputChar; /* Store the input character from the user */

	printf("Enter any character (or Press Ctrl+D to end input):\n");
	iInputChar = getchar();
	printf("The value of getchar() != EOF is: %d\n", iInputChar != EOF);

	return 0;
} /* End main() */
