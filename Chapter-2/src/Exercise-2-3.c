/*
 * This program converts string of hexadecimal digits into its equivalent integer
 * value.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdbool.h>
#include <stdio.h>

/** REQUIRED MACRO */
#define MAXLENGTH	100	/* Maximum input length */

/** FUNCTION PROTOTYPES */
int hexToInt(char cHex[]);
bool isValidHex(const char cHex[]);

/** MAIN PROGRAM */
/*
 * main: It calls hexToInt() function to convert hexadecimal strings into integer value.
 */
int main(void)
{
	char cHexValue[MAXLENGTH];	/* Store the hexadecimal value */
	int iConvertedValue;		/* Store the converted integer */

	while (1) {
		printf("Enter the hexadecimal value: ");
		scanf("%s", cHexValue);

		if (isValidHex(cHexValue)) {
			iConvertedValue = hexToInt(cHexValue);
			printf("After converting to integer: %d\n", iConvertedValue);
			break;
		} else {
			printf("Invalid hexadecimal number. Please enter valid number.\n");
		}
	}

	return 0;
} /* End main() */

/*
 * hexToInt	: Converts a string of hexadecimal digits (with an optional "0x" or "0X" prefix)
 *		  into its equivalent integer value.
 * Input	: cHex (An array of string containing the hexadecimal digits)
 * Return	: Integer equivalent of the hexadecimal string
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */
int hexToInt(char cHex[])
{
	int i = 0;		/* Index variable to iterate in the loop */
	int iResult = 0;	/* Store the final result */
	int iHexNum;		/* Store the value of each hexadecimal digit */

	if (cHex[i] == '0' && (cHex[i + 1] == 'x' || cHex[i + 1] == 'X'))
		i = i + 2;

	while ((cHex[i] >= '0' && cHex[i] <= '9') || (cHex[i] >= 'a' && cHex[i] <= 'f')
			|| (cHex[i] >= 'A' && cHex[i] <= 'F')) {

		if (cHex[i] >= '0' && cHex[i] <= '9')
			iHexNum = cHex[i] - '0';
		else if (cHex[i] >= 'a' && cHex[i] <= 'f')
			iHexNum = cHex[i] - 'a' + 10;
		else
			iHexNum = cHex[i] - 'A' + 10;

		iResult = (iResult << 4) + iHexNum;
		i++;
	}

	return iResult;
} /* End hexToInt() */

/*
 * isValidHex	: Checks if the given string contains valid hexadecimal characters.
 * Input	: cHex (An array of string containing the hexadecimal digits)
 * Return	: true if valid, false otherwise.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */
bool isValidHex(const char cHex[])
{
	int i = 0;	/* Index variable to iterate in loop */

	if (cHex[i] == '0' && (cHex[i + 1] == 'x' || cHex[i + 1] == 'X'))
		i += 2;

	while (cHex[i] != '\0') {
		if (!((cHex[i] >= '0' && cHex[i] <= '9') ||
					(cHex[i] >= 'a' && cHex[i] <= 'f') ||
					(cHex[i] >= 'A' && cHex[i] <= 'F'))) {
			return false; /* Invalid character */
		}
		i++;
	}

	return true; /* All characters are valid */
} /* End isValidHex() */
