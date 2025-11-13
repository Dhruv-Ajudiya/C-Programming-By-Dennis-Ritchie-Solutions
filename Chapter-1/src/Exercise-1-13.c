/*
 * This program prints a histogram of the lengths of words in its input.
 * Author	: Dhruv Ajudiya
 * Created	: 13 August 2024
 * Modified	: 13 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MAIN PROGRAM */
/*
 * main: Print a histogram of the lengths of words in its input.
 */
int main(void)
{
	int iInputChar; /* Store the input character from user */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	printf("Each line of asterisks represents the length of a word\n");
	while ((iInputChar = getchar()) != EOF) {
		if (iInputChar == ' ' || iInputChar == '\n' || iInputChar == '\t')
			putchar('\n');
		else
			putchar('*');
	}

	return 0;
} /* End main() */
