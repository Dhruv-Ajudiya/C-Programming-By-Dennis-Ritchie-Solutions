/*
 * This progarm writes a function setBits(x, p, n, y) that returns 'x' with the 'n' bits
 * that begin at position 'p' set to the rightmost 'n' bits of 'y', leaving the other
 * bits unchanged.
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <limits.h>

/** FUNCTION PROTOTYPES */
unsigned int setBits(unsigned int uiX, int iPos, int iNumBits, unsigned int uiY);

/** MAIN PROGRAM */
/*
 * main: It reads values of 'x', 'p', 'n', and 'y' from the user and calls the setBits()
 *	 function to modify the 'n' bits in 'x' starting at position 'p' with the rightmost
 *	 'n' bits of 'y'.
 */
int main(void)
{
	unsigned int uiX = 0;	/* Store the value of x */
	unsigned int uiY = 0;	/* Store the value of y */
	int iPos = 0;		/* Store the position p */
	int iNumBits = 0;	/* Store the number of bits n */
	unsigned int uiResult;	/* Store the final result */
	int iBitSize = sizeof(unsigned int) * CHAR_BIT; /* Total number of bits in unsigned int */

	printf("Enter the value of x: ");
	scanf("%u", &uiX);
	if ((int)uiX < 0) {
		printf("Error: Please enter a positive value for x\n");
		return 1;
	}

	printf("Enter the value of y: ");
	scanf("%u", &uiY);
	if ((int)uiY < 0) {
		printf("Error: Please enter a positive value for y\n");
		return 1;
	}

	printf("Enter the value of position: ");
	scanf("%d", &iPos);
	if (iPos < 0 || iPos >= iBitSize) {
		printf("Error: Position is out of bounds. Enter between 0 and %d.\n", iBitSize - 1);
		return 1;
	}

	printf("Enter the number of bits: ");
	scanf("%d", &iNumBits);
	if (iNumBits <= 0 || iPos + 1 < iNumBits) {
		printf("Error: Insufficient bits. no of bits >= position + 1.\n");
		return 1;
	}

	uiResult = setBits(uiX, iPos, iNumBits, uiY);
	printf("Result is: %u\n", uiResult);

	return 0;
} /* End main() */

/*
 * setBits	: Modifies the 'n' bits starting at position 'p' with the rightmost
 *		  'n' bits of 'y', leaving the other bits in 'x' unchanged.
 * Input	: uiX (original value to modify)
 *		  iPos (starting position for modification)
 *		  iNumBits (number of bits to modify)
 *		  uiY (value providing the new bits)
 * Return	: Modified value of uiX with the specified bits changed
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */
unsigned int setBits(unsigned int uiX, int iPos, int iNumBits, unsigned int uiY)
{
	/* Mask to clear the iNumBits bits at position iPos in uiX */
	unsigned int uiXMask = ~(~(~0U << iNumBits) << (iPos + 1 - iNumBits));

	/* Mask to extract the rightmost iNumBits bits from uiY and position them at iPos */
	unsigned int uiYMask = (uiY & ~(~0U << iNumBits)) << (iPos + 1 - iNumBits);

	return (uiX & uiXMask) | uiYMask;
} /* End setBits() */
