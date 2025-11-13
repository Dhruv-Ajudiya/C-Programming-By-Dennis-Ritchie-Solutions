/*
 * This program reads a floating-point number from input and stores it in a variable.
 * It validates the input and prints the number if valid, otherwise informs the user
 * of invalid input.
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
int getFloat(double *dInputNumber);

/** MAIN PROGRAM */
/*
 * main: It takes input floating point number from the user and prints the number if valid.
 *	 If the input is not a valid floating point number, it displays an appropriate message.
 */
int main(void)
{
	double dNumber; /* Store the input floating point number */

	printf("Enter the number: ");
	if (getFloat(&dNumber))
		printf("Entered number is: %lf\n", dNumber);
	else
		printf("Invalid input. Enter the valid number.\n");

	return 0;
} /* End main() */

/*
 * getFloat	: Reads the next floating point number from input and stores it in *dInputNumber.
 * Input	: dInputNumber (pointer to a double where the result will be stored)
 * Return	: Returns the last character read from input if valid,
 *		  otherwise 0 for invalid input
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */
int getFloat(double *dInputNumber)
{
	int iInputCharacter;	/* Store the current character from input */
	int iSign;		/* Store the sign of the number */
	double dPower;		/* Store the divisor for the fractional part */

	/* Skip white space */
	while (isspace(iInputCharacter = getCharacter()))
		;

	/* Check if the input is not a number, '+' or '-' */
	if (!isdigit(iInputCharacter) && iInputCharacter != EOF	&& iInputCharacter != '+'
			&& iInputCharacter != '-' && iInputCharacter != '.') {
		ungetCharacter(iInputCharacter);
		return 0;
	}

	/* Determine the sign */
	iSign = (iInputCharacter == '-') ? -1 : 1;

	/* Check for '+' or '-' followed by a digit */
	if (iInputCharacter == '+' || iInputCharacter == '-')
		iInputCharacter = getCharacter();

	/* Read the integer part of the number */
	for (*dInputNumber = 0; isdigit(iInputCharacter); iInputCharacter = getCharacter())
		*dInputNumber = 10 * *dInputNumber + (iInputCharacter - '0');

	/* Read the fractional part of the number */
	if (iInputCharacter == '.')
		iInputCharacter = getCharacter();

	for (dPower = 1.0; isdigit(iInputCharacter); iInputCharacter = getCharacter()) {
		*dInputNumber = 10 * *dInputNumber + (iInputCharacter - '0');
		dPower *= 10.0;
	}

	*dInputNumber = *dInputNumber * iSign / dPower;

	/* Push back the character if it's not EOF */
	if (iInputCharacter != EOF)
		ungetCharacter(iInputCharacter);

	return iInputCharacter;
} /* End getFloat() */

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
