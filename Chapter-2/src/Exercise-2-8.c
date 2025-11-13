/*
 * This program rotates the bits of an integer to the right by a specified
 * number of positions.
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <limits.h>

/** FUNCTION PROTOTYPES */
unsigned int rightRot(unsigned int uiNum, int iPos);

/** MAIN PROGRAM */
/*
 * main: It reads an integer value 'x' and the number of positions 'n' from the user, then
 *	 calls the rightRot() function to rotate the bits of 'x' to the right by 'n' positions.
 */
int main(void)
{
	unsigned int uiNum;	/* Store the integer whose bits are to be rotated */
	int iPos;		/* Store the number of positions to rotate */
	unsigned int uiRes;	/* Store the result of rightRot() function */

	printf("Enter the integer: ");
	scanf("%u", &uiNum);
	if ((int)uiNum < 0) {
		printf("Error: Please enter a positive value\n");
		return 1;
	}

	printf("Enter the number of positions to rotate: ");
	scanf("%d", &iPos);
	if (iPos < 0) {
		printf("Error: Please enter a positive value\n");
		return 1;
	}
	uiRes = rightRot(uiNum, iPos);
	printf("Result after rotating: %u\n", uiRes);

	return 0;
} /* End main() */

/*
 * rightRot	: Rotates the bits of a number to the right by specified positions
 * Input	: uiNum (Integer whose bits are to be rotated)
 *		  iPos (Number of positions to rotate the bits)
 * Return	: The integer value after rotating the bits of a number to the right
 *		  by specified positions
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */
unsigned int rightRot(unsigned int uiNum, int iPos)
{
	/* Total number of bits in unsigned int for the machine */
	int iBitSize = sizeof(unsigned int) * CHAR_BIT;
	/* Mask to extract the rightmost 'iPos' bits from 'uiNum' */
	unsigned int uiMask;
	
	iPos = iPos % iBitSize;
	if (iPos == 0)
		return uiNum;

	uiMask = uiNum & (~(~0U << iPos));
	uiNum = uiNum >> iPos;
	uiMask = uiMask << (iBitSize - iPos);

	return uiMask | uiNum;
} /* End rightRot() */
