/*
 * This program prints Celsius to Fahrenheit table on the console.
 * Author	: Dhruv Ajudiya
 * Created	: 12 August 2024
 * Modified	: 12 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MAIN PROGRAM */
/*
 * main: Print Celsius to Fahrenheit table for celsius = 0, 20, ..., 300,
 */
int main(void)
{
	float fFahr;	/* Fahrenheit temperature */
	float fCelsius;	/* Celsius temperature */
	float fLower, fUpper, fStep;

	fLower = 0;	/* Lower limit of temperatuire scale */
	fUpper = 300;	/* Upper limit */
	fStep = 20;	/* Step size */
	fCelsius = fLower;

	printf("Celsius Fahrenheit\n");
	while (fCelsius <= fUpper) {
		fFahr = (9.0 / 5.0 * fCelsius) + 32.0;
		printf("%7.0f %10.1f\n", fCelsius, fFahr);
		fCelsius = fCelsius + fStep;
	}

	return 0;
} /* End main() */
