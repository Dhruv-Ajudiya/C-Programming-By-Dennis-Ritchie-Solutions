/*
 * This program prints Fahrenheit to Celsius table on the console in reverse order.
 * Author	: Dhruv Ajudiya
 * Created	: 12 August 2024
 * Modified	: 12 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MAIN PROGRAM */
/*
 * main: Print Fahrenheit to Celsius table for fahr = 300, 280, ..., 0.
 */
int main(void)
{
	float fFahr;	/* Fahrenheit temperaure */
	float fCelsius; /* Celsius temperature */
	float fLower, fUpper, fStep;

	fLower = 0;	/* Lower limit of temperatuire scale */
	fUpper = 300;	/* Upper limit */
	fStep = 20;	/* Step size */
	fFahr = fLower;

	printf("Fahrenheit Celsius\n");
	for (fFahr = fUpper; fFahr >= fLower; fFahr = fFahr - fStep) {
		fCelsius = (5.0 / 9.0) * (fFahr - 32.0);
		printf("%10.0f %7.1f\n", fFahr, fCelsius);
	}

	return 0;
} /* End main() */
