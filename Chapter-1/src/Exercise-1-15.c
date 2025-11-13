/*
 * This program converts temperature from Celsius to Fahrenheit on the console using function.
 * Author	: Dhruv Ajudiya
 * Created	: 13 August 2024
 * Modified	: 13 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** FUNCTION PROTOTYPES */
float celsiusToFahrenheit(float fFahr);

/** MAIN PROGRAM */
/*
 * main: It takes the temperature in celsius from user and calculates temperature in fahrenheit
 *	 by calling celsiusToFahrenheit() function.
 */
int main(void)
{
	float fFahr;	/* Temperature in fahrenheit */
	float fCelsius;	/* Temperature in celius */

	printf("Enter the temperature in Celsius: ");
	if (scanf("%f", &fCelsius) != 1) {
		printf("Please enter valid number\n");
		return 1;
	}
	fFahr = celsiusToFahrenheit(fCelsius);
	printf("Temperaure in Fahrenheit is: %.2f\n", fFahr);

	return 0;
} /* End main() */

/*
 * celsiusToFahrenheit	: Calculates the fahrenheit temperature from celsius temperature.
 * Input		: fCelsius (Temperature in celsius)
 * Return		: Temperature in fahrenheit
 * Author		: Dhruv Ajudiya
 * Created		: 13 August 2024
 * Modified		: 13 August 2024
 */
float celsiusToFahrenheit(float fCelsius)
{
	float fFahr; /* temperature in fahrenheit */

	fFahr = (9.0 / 5.0) * fCelsius + 32;
	return fFahr;
} /* End celsiusToFahrenheit() */
