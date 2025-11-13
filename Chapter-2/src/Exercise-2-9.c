/*
 * This program counts the number of '1' bits in an integer using an
 * optimized method that uses the property of two's complement numbers,
 * where x &= (x-1) deletes the rightmost '1' bit in x.
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** FUNCTION PROTOTYPES */
int bitCount(unsigned int uNumber);

/** MAIN PROGRAM */
/*
 * main: It takes integer from user and calls bitCount() function to
 *	 count the number of '1' bits in it.
 */
int main(void)
{
	unsigned int uiInputNum;	/* Store the number from the user */
	int iCount;			/* Store the count of 1 bits */

	printf("Enter an unsigned integer: ");
	scanf("%u", &uiInputNum);

	iCount = bitCount(uiInputNum);
	printf("The number of 1 bits in %u is: %d\n", uiInputNum, iCount);

	return 0;
} /* End main() */

/*
 * bitCount	: Counts the number of '1' bits in an integer using the optimized method
 *		  x &= (x-1), which clears the rightmost 1 bit
 * Input	: uiNum (an unsigned integer whose '1' bits are to be counted)
 * Return	: Returns the count of '1' bits in the input number
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */
int bitCount(unsigned int uiNum)
{
	int iBitCount = 0; /* Store the count of '1' bits */

	for (iBitCount = 0; uiNum != 0; iBitCount++)
		uiNum &= (uiNum - 1);

	return iBitCount;
} /* End bitCount() */
