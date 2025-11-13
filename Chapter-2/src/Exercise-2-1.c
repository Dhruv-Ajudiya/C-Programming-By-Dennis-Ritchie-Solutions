/*
 * This program calculates and prints the ranges of char, short, int, and long variables,
 * both signed and unsigned, by printing appropriate values from standard headers and by
 * direct computation. It also determines the ranges of various floating-point types.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <limits.h>
#include <float.h>

/** MAIN PROGRAM */
/*
 * main: It prints the ranges of various integer and floating-point data types from standard
 *	 headers. It also prints the ranges of various integer data types by direct computation.
 */
int main(void)
{
	/* Ranges of various integer and floating-point types from standard headers */
	printf("Ranges of various integer and floating-point types (from standard headers):\n");
	printf("Signed Char	: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("Unsigned Char	: 0 to %u\n", UCHAR_MAX);
	printf("Signed Short	: %d to %d\n", SHRT_MIN, SHRT_MAX);
	printf("Unsigned Short	: 0 to %u\n", USHRT_MAX);
	printf("Signed Int	: %d to %d\n", INT_MIN, INT_MAX);
	printf("Unsigned Int	: 0 to %u\n", UINT_MAX);
	printf("Signed Long	: %ld to %ld\n", LONG_MIN, LONG_MAX);
	printf("Unsigned Long	: 0 to %lu\n", ULONG_MAX);

	printf("Float		: %E to %E\n", FLT_MIN, FLT_MAX);
	printf("Double		: %E to %E\n", DBL_MIN, DBL_MAX);
	printf("Long Double	: %LE to %LE\n", LDBL_MIN, LDBL_MAX);

	/* Ranges of various integer and floating-point types (by direct computation) */
	printf("\nRanges of various integer types (by direct computation):\n");
	printf("Signed Char	: %d to %d\n", -(char)((unsigned char)~0 >> 1) - 1,
						(char)((unsigned char)~0 >> 1));
	printf("Unsigned Char	: 0 to %u\n", (unsigned char)~0);
	printf("Signed Short	: %d to %d\n", -(short)((unsigned short)~0 >> 1) - 1,
						(short)((unsigned short)~0 >> 1));
	printf("Unsigned Short	: 0 to %u\n", (unsigned short)~0);
	printf("Signed Int	: %d to %d\n", -(int)((unsigned int)~0 >> 1) - 1,
						(int)((unsigned int)~0 >> 1));
	printf("Unsigned Int	: 0 to %u\n", (unsigned int)~0);
	printf("Signed Long	: %ld to %ld\n", -(long)((unsigned long)~0 >> 1) - 1,
						(long)((unsigned long)~0 >> 1));
	printf("Unsigned Long	: 0 to %lu\n", (unsigned long)~0);

	return 0;
} /* End main() */
