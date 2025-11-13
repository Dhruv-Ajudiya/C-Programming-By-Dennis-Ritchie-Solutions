/*
 * This program copies the input to its output, replacing each tab by '\t', each
 * backspace by '\b', and each backslash by '\\'.
 * Author	: Dhruv Ajudiya
 * Created	: 12 August 2024
 * Modified	: 12 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MAIN PROGRAM */
/*
 * main: Copy the input to its output, replacing each tab by '\t', each backspace
 *	 by '\b', and each backslash by '\\'.
 */
int main(void)
{
	int iInputChar; /* Store the input character from the user */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iInputChar = getchar()) != EOF) {
		if (iInputChar == '\t') {
			putchar('\\');
			putchar('t');
		}
		if (iInputChar == '\b') {
			putchar('\\');
			putchar('b');
		}
		if (iInputChar == '\\') {
			putchar('\\');
			putchar('\\');
		}

		if (iInputChar != '\t' && iInputChar != '\b' && iInputChar != '\\')
			putchar(iInputChar);
	}

	return 0;
} /* End main() */
