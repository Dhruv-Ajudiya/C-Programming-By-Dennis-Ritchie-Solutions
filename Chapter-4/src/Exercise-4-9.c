/*
 * This program demonstrates functions that allow pushing back a single input
 * character and reading it again, with special handling for EOF.
 * Author	: Dhruv Ajudiya
 * Created	: 28 August 2024
 * Modified	: 09 September 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** GLOBAL VARIABLES */
int cInputBuffer;	/* Buffer to store input pushed back into input */
int iBufferFlag;	/* Flag to indicate whether the  buffer is empty */

/** FUNCTION PROTOTYPES */
int getCharacter(void);
void ungetCharacter(int iInputCharacter);

/** MAIN PROGRAM */
/*
 * main: It takes input from user and reads only the first charcter from the line, pushes
 *	 that character into buffer and prints the pushed back character. The program will
 *	 run until the user presses EOF.
 */
int main(void)
{
	int iInputChar; /* Store the input character from user */

	printf("Enter input string (press Ctrl+D to end):\n");
	while ((iInputChar = getchar()) != EOF) {
		/* Read only the first character of each line */
		if (iInputChar == '\n')
			continue;

		ungetCharacter(iInputChar); /* Push back the first character */
		printf("Reading pushed-back character: %c\n", getCharacter());

		/* Skip the rest of the characters in the line */
		while ((iInputChar = getchar()) != '\n' && iInputChar != EOF)
			;
	}
	ungetCharacter(EOF);
	if (getCharacter() == EOF)
		printf("EOF encountered\n");

	return 0;
} /* End main() */

/*
 * getCharacter	: Gets a (possibly pushed-back) character from input
 * Return	: The character read from input or from buffer
 * Author	: Dhruv Ajudiya
 * Created	: 28 August 2024
 * Modified	: 28 August 2024
 */
int getCharacter(void)
{
	if (iBufferFlag != 0) {
		iBufferFlag = 0;
		return cInputBuffer;
	} else {
		return getchar();
	}
} /* End getCharacter() */

/*
 * ungetCharacter	: Pushes a character back into the input buffer
 * Input		: iInputCharacter (the character to push back)
 * Author		: Dhruv Ajudiya
 * Created		: 28 August 2024
 * Modified		: 28 August 2024
 */
void ungetCharacter(int iInputCharacter)
{
	if (iBufferFlag != 0) {
		printf("Error: only one charcter is allowed to pushback\n");
	} else {
		cInputBuffer = iInputCharacter;
		iBufferFlag = 1;
	}
} /* End ungetCharacter() */
