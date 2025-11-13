/*
 * This program checks if one string appears at the end of another string.
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>

/** MACRO DEFINITIONS */
#define MAXSTRINGSIZE	100	/* Maximum size for input strings */

/** FUNCTION PROTOTYPES */
int strEnd(char *cSourceStr, char *cSearchStr);
void removeNewline(char *cInputStr);

/** MAIN PROGRAM */
/*
 * main: Reads two strings from the user and checks if the second string 
 *	 appears at the end of the first string.
 */
int main(void)
{
	char cFirstStr[MAXSTRINGSIZE];	/* Store first input string */
	char cSecondStr[MAXSTRINGSIZE];	/* Store second input string */

	printf("Enter the first string: ");
	fgets(cFirstStr, MAXSTRINGSIZE, stdin);
	removeNewline(cFirstStr);

	printf("Enter the second string: ");
	fgets(cSecondStr, MAXSTRINGSIZE, stdin);
	removeNewline(cSecondStr);

	if (strEnd(cFirstStr, cSecondStr))
		printf("String found at the end.\n");
	else
		printf("String not found at the end.\n");

	return 0;
} /* End main() */

/*
 * strEnd	: Checks if the search string appears at the end of the source string.
 * Input	: cSourceStr (pointer to the source string)
 *		  cSearchStr (pointer to the search string)
 * Return	: 1 if the search string appears at the end, otherwise 0.
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */
int strEnd(char *cSourceStr, char *cSearchStr)
{
	unsigned int iLengthSource = strlen(cSourceStr); /* Store the length of the source string */
	unsigned int iLengthSearch = strlen(cSearchStr); /* Store the length of the search string */

	if (iLengthSearch > iLengthSource)
		return 0;

	cSourceStr += iLengthSource - iLengthSearch;

	while (*cSourceStr != '\0' && *cSearchStr != '\0') {
		if (*cSourceStr++ != *cSearchStr++)
			return 0; /* Mismatch found */
	}

	return 1; /* Match found */
} /* End strEnd() */

/*
 * removeNewline	: Removes the newline character from the end of a string.
 * Input		: cInputStr (pointer to the string to be processed)
 * Author		: Dhruv Ajudiya
 * Created		: 7 October 2024
 * Modified		: 7 October 2024
 */
void removeNewline(char *cInputStr)
{
	while (*cInputStr != '\0') {
		if (*cInputStr == '\n') {
			*cInputStr = '\0';
			break;
		}
		cInputStr++;
	}
} /* End removeNewline() */
