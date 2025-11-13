/*
 * This program reads an integer input from the user and verifies its validity.
 * If the input is not valid (such as '+' or '-' not followed by a digit), it pushes
 * the characters back into the input buffer.
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <ctype.h>

/** MACRO DEFINITIONS */
#define BUFFER_SIZE	100	/* Size of buffer for pushed back input */

/** GLOBAL VARIABLES */
char cInputBuffer[BUFFER_SIZE];	/* Buffer to store input pushed back into input */
int iBufferPosition;		/* Next free position in input buffer */

/** FUNCTION PROTOTYPES */
int getCharacter(void);
void ungetCharacter(int iInputCharacter);
int getInteger(int *iInputNumber);

/** MAIN PROGRAM */
/*
 * main: It takes input integer from the user and prints the integer if valid.
 *	 If the input is not a valid integer, it displays an appropriate message.
 */
int main(void)
{
	int iNumber; /* Store the input integer from user */

	printf("Enter an integer: ");

	if (getInteger(&iNumber))
		printf("The integer is: %d\n", iNumber);
	else
		printf("Invalid input. Enter a valid number.\n");

	return 0;
} /* End main() */

/*
 * getInteger	: Reads the next integer from input and stores it in *iInputNumber.
 * Input	: iInputNumber (pointer to an integer where the result will be stored)
 * Return	: Returns the last character read from input if valid,
 *		  otherwise 0 for invalid input.
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */
int getInteger(int *iInputNumber)
{
	int iInputCharacter;	/* Store the current character from input */
	int iSign;		/* Store the sign of the number */
	int iNextCharacter;	/* Store the next character after sign */

	/* Skip white space */
	while (isspace(iInputCharacter = getCharacter()))
		;

	/* Check if the input is not a number, '+' or '-' */
	if (!isdigit(iInputCharacter) && iInputCharacter != EOF
			&& iInputCharacter != '+' && iInputCharacter != '-') {
		ungetCharacter(iInputCharacter);
		return 0;
	}

	/* Determine the sign */
	iSign = (iInputCharacter == '-') ? -1 : 1;

	/* Check for '+' or '-' followed by a digit */
	if (iInputCharacter == '+' || iInputCharacter == '-') {
		iNextCharacter = getCharacter();
		if (!isdigit(iNextCharacter)) {
			ungetCharacter(iNextCharacter);		/* Push back the non-digit */
			ungetCharacter(iInputCharacter);	/* Push back the sign */
			return 0;
		}
		iInputCharacter = iNextCharacter;	/* Continue with the next character */
	}

	/* Read the number */
	for (*iInputNumber = 0; isdigit(iInputCharacter); iInputCharacter = getCharacter())
		*iInputNumber = 10 * *iInputNumber + (iInputCharacter - '0');
	*iInputNumber *= iSign;

	/* Push back the character if it's not EOF */
	if (iInputCharacter != EOF)
		ungetCharacter(iInputCharacter);

	return iInputCharacter;
} /* End getInteger() */

/*
 * getCharacter	: Gets a (possibly pushed-back) character from input
 * Return	: The character read from input
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */
int getCharacter(void)
{
	return (iBufferPosition > 0) ? cInputBuffer[--iBufferPosition] : getchar();
} /* End getCharacter() */

/*
 * ungetCharacter	: Pushes a character back into the input buffer
 * Input		: iInputCharacter (the character to push back)
 * Author		: Dhruv Ajudiya
 * Created		: 7 October 2024
 * Modified		: 7 October 2024
 */
void ungetCharacter(int iInputCharacter)
{
	if (iBufferPosition >= BUFFER_SIZE)
		printf("Error: Input buffer overflow\n");
	else
		cInputBuffer[iBufferPosition++] = iInputCharacter;
} /* End ungetCharacter */

