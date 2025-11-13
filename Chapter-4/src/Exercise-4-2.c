/**
 * This program converts a string to a floating point number using user defined function
 * that handles the scientific notation.
 * Author	: Dhruv Ajudiya
 * Created	: 23 August 2024
 * Modified	: 23 August 2024
 */

/** REQUIRED HEADER FILES */
#include <ctype.h>
#include <stdio.h>

/** MACRO DEFINITIONS */
#define MAXLENGTH	1000	/* Maximum input line length */

/** FUNCTION PROTOTYPES */
int getLine(char cLine[], int iMaxLen);
double convertStringToFloat(char cInputString[]);

/** MAIN PROGRAM */
/*
 * main: Reads a input string from the user, then it calls convertStringToFloat() function
 *	 and converts it to a floating point value, and prints the result on console.
 */
int main(void)
{
	char cInputString[MAXLENGTH];	/* Store input string from user */
	double dResult;			/* Store converted floating point value */

	printf("Enter a string to convert to float: ");
	getLine(cInputString, MAXLENGTH);

	dResult = convertStringToFloat(cInputString);
	printf("Converted float value: %f\n", dResult);

	return 0;
} /* End main() */

/*
 * convertStringToFloat	: Converts the given string to a floating point value
 * Input		: cInputString (input string)
 * Return		: Converted floating point value
 * Author		: Dhruv Ajudiya
 * Created		: 23 August 2024
 * Modified		: 23 August 2024
 */
double convertStringToFloat(char cInputString[])
{
	double dValue;	/* Stores the numeric value of the converted string */
	double dPower;	/* Stores the power to handle decimal places */
	int iSign;	/* Stores the sign of the number */
	int i;		/* Index variable to iterate in the loop */
	int iExpSign;	/* Stores the sign of the exponent */
	int iExponent;	/* Stores the exponent part of the number */

	for (i = 0; isspace(cInputString[i]); i++)
		;

	iSign = (cInputString[i] == '-') ? -1 : 1;
	if (cInputString[i] == '+' || cInputString[i] == '-')
		i++;

	for (dValue = 0.0; isdigit(cInputString[i]); i++)
		dValue = 10.0 * dValue + (cInputString[i] - '0');

	if (cInputString[i] == '.')
		i++;

	for (dPower = 1.0; isdigit(cInputString[i]); i++) {
		dValue = 10.0 * dValue + (cInputString[i] - '0');
		dPower *= 10.0;
	}

	/* Handle exponent if present */
	if (cInputString[i] == 'e' || cInputString[i] == 'E')
		i++;
	iExpSign = (cInputString[i] == '-') ? -1 : 1;
	if (cInputString[i] == '+' || cInputString[i] == '-')
		i++;
	for (iExponent = 0; isdigit(cInputString[i]); i++)
		iExponent = 10 * iExponent + (cInputString[i] - '0');

	/* Apply exponent */
	if (iExpSign == -1) {
		while (iExponent-- > 0)
			dPower *= 10.0;
		return iSign * (dValue / dPower);
	} else {
		while (iExponent-- > 0)
			dValue *= 10.0;
		return iSign * (dValue / dPower);
	}
} /* End convertStringToFloat() */

/*
 * getLine	: Reads a line from the console
 * Input	: cLine (character array to store the input line)
 *		  iMaxLen (maximum length of the line that can be stored)
 * Return	: Length of the input line
 * Author	: Dhruv Ajudiya
 * Created	: 23 August 2024
 * Modified	: 23 August 2024
 */
int getLine(char cLine[], int iMaxLen)
{
	int iInputChar;	/* Store the input character from user */
	int i;		/* Index variable to iterate in the loop */

	for (i = 0; i < iMaxLen - 1 && (iInputChar = getchar()) != EOF && iInputChar != '\n'; i++)
		cLine[i] = iInputChar;

	if (iInputChar == '\n') {
		cLine[i] = iInputChar;
		i++;
	}
	cLine[i] = '\0';

	return i; /* Length of the string */
} /* End getLine() */
