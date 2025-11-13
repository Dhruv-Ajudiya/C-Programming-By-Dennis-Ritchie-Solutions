/*
 * This program writes the function any(s1,s2), which returns the first location
 * in a string s1 where any character from the string s2 occurs, or -1 if s1
 * contains no characters from s2.
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** FUNCTION PROTOTYPES */
int any(char cFirstStr[], char cSecondStr[]);

/** MAIN PROGRAM */
/*
 * main: It reads two strings from the user and calls the any() function to find
 *	 the first location in the first string where any character from the second
 *	 string occurs.
 */
int main(void)
{
	char cFirstStr[50];	/* Store the first string */
	char cSecondStr[50];	/* Store the second string */
	int iLocation;		/* Store the result of the any() function */

	printf("Enter the first string: ");
	scanf("%[^\n]%*c", cFirstStr); /* Using scanset to read the entire line */
	printf("Enter the second string: ");
	scanf("%[^\n]%*c", cSecondStr);

	iLocation = any(cFirstStr, cSecondStr);
	if (iLocation != -1)
		printf("The first location found is (0-indexed): %d\n", iLocation);
	else
		printf("No characters from the second string found in the first string\n");

	return 0;
} /* End main() */

/*
 * any		: Returns the first location in the first string where any character from
 *		  the second string occurs, or -1 if first string contains no characters
 *		  from second string.
 * Input	: cFirstStr (an array containing the first string)
 *		  cSecondStr (an array containing the second string)
 * Return	: Index of the first occurrence, or -1 if no character is found
 * Author	: Dhruv Ajudiya
 * Created	: 20 August 2024
 * Modified	: 20 August 2024
 */
int any(char cFirstStr[], char cSecondStr[])
{
	int i, j; /* Index variable for the first and second strings */

	for (i = 0; cFirstStr[i] != '\0'; i++) {
		for (j = 0; cSecondStr[j] != '\0'; j++) {
			if (cFirstStr[i] == cSecondStr[j])
				return i;
		}
	}

	return -1; /* If no character is found */
} /* End any() */
