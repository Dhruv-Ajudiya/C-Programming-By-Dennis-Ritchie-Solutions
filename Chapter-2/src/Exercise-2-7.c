/*
 * This program inverts 'n' bits starting at position 'p' in the integer 'x',
 * leaving the other bits unchanged.
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */

/** REQUIRED HEADER FILES */
#include <limits.h>
#include <stdio.h>

/** FUNCTION PROTOTYPES */
unsigned int invert(unsigned int uiNum, int iPos, int iNumBits);

/** MAIN PROGRAM */
/*
 * main: It takes input integer 'x', position 'p', and number of bits 'n' from the user.
 *	 It calls the invert() function to invert the specified bits in 'x' and
 *	 displays the result.
 */
int main(void)
{
	unsigned int uiNum;	/* Number whose bits are to be inverted */
	int iPos;		/* Position at which the inversion starts */
	int iNumBits;		/* Number of bits to invert */
	unsigned int uiResult;	/* Store the result of the invert() function */
	int iBitSize = sizeof(unsigned int) * CHAR_BIT; /* Total number of bits in unsigned int */

	printf("Enter the integer value: ");
	scanf("%u", &uiNum);
	if ((int)uiNum < 0) {
		printf("Error: Please enter a positive number\n");
		return 1;
	}

	printf("Enter the position: ");
	scanf("%d", &iPos);
	if (iPos < 0 || iPos >= iBitSize) {
		printf("Error: Position is out of bounds. Enter between 0 and %d.\n", iBitSize - 1);
		return 1;
	}

	printf("Enter the number of bits to invert: ");
	scanf("%d", &iNumBits);
	if (iNumBits <= 0 || iPos + 1 < iNumBits) {
		printf("Error: Insufficient bits. no of bits >= position + 1.\n");
		return 1;
	}

	uiResult = invert(uiNum, iPos, iNumBits);
	printf("Result after inverting: %u\n", uiResult);

	return 0;
} /* End main() */

/*
 * invert	: Inverts 'n' bits of 'iNum' starting from position 'iPos'
 * Input	: iNum (Integer whose bits are to be inverted)
 *		  iPos (Position at which the inversion starts, 0-indexed from the right)
 *		  iNumBits (Number of bits to invert)
 * Return	: The integer with the specified bits inverted
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */
unsigned int invert(unsigned int uiNum, int iPos, int iNumBits)
{
	/* Mask with 'iNumBits' set at the position 'iPos' */
	unsigned int uiMask = (~(~0U << iNumBits)) << (iPos + 1 - iNumBits);

	return uiNum ^ uiMask;
} /* End invert() */
