/*
 * This Program demonstrates the ungetString() function that pushes back the entire
 * string onto the input buffer.
 * Author	: Dhruv Ajudiya
 * Created	: 27 August 2024
 * Modified	: 27 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>

/** MACRO DEFINITIONS */
#define BUFFER_SIZE	100	/* Size of buffer for pushed back input */
#define MAXLENGTH	100	/* Maximum size of the input string */

/** GLOBAL VARIABLES */
char cInputBuffer[BUFFER_SIZE];	/* Buffer to store input pushed back into input */
int iBufferPosition;		/* Next free position in input buffer */

/** FUNCTION PROTOTYPES */
void ungetString(char cInputString[]);
int getCharacter(void);
void ungetCharacter(int iInputCharacter);

/** MAIN PROGRAM */
/*
 * main: It takes input string from user and calls ungetString() function to push back the
 *	 entire string onto the stack.
 */
int main(void)
{
	char cInputString[MAXLENGTH];	/* Input string entered by user */
	int iInputChar;			/* Store the input character from the user */
	int i = 0;			/* Index variable to iterate in loop */

	printf("Enter the string (press Enter to end input):\n");
	while ((iInputChar = getchar()) != EOF && i < MAXLENGTH - 1)
		cInputString[i++] = iInputChar;
	cInputString[i] = '\0';

	ungetString(cInputString);

	printf("\nCharacters retrieved from the buffer:\n");
	while ((iInputChar = getCharacter()) != EOF)
		putchar(iInputChar);
	printf("\n");

	return 0;
} /* End main() */

/*
 * ungetString	: Pushes the string back into input buffer
 * Input	: cInputString (the string to push back)
 * Author	: Dhruv Ajudiya
 * Created	: 27 August 2024
 * Modified	: 27 August 2024
 */
void ungetString(char cInputString[])
{
	int iLength = strlen(cInputString); /* Store the length of the string */

	while (iLength > 0)
		ungetCharacter(cInputString[--iLength]);
} /* End ungetString() */

/*
 * getCharacter	: Gets a (possibly pushed-back) character from input
 * Return	: The character read from input
 * Author	: Dhruv Ajudiya
 * Created	: 27 August 2024
 * Modified	: 27 August 2024
 */
int getCharacter(void)
{
	return (iBufferPosition > 0) ? cInputBuffer[--iBufferPosition] : getchar();
} /* End getCharacter() */

/*
 * ungetCharacter	: Pushes a character back into the input buffer
 * Input		: iInputCharacter (the character to push back)
 * Author		: Dhruv Ajudiya
 * Created		: 27 August 2024
 * Modified		: 27 August 2024
 */
void ungetCharacter(int iInputCharacter)
{
	if (iBufferPosition >= BUFFER_SIZE)
		printf("Error: Input buffer overflow\n");
	else
		cInputBuffer[iBufferPosition++] = iInputCharacter;
} /* End ungetCharacter() */
