/*
 * This program concatenates two strings using a pointer version of strcat.
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MACRO DEFINITIONS */
#define MAXSTRINGSIZE	100	/* Maximum size for strings */

/** FUNCTION PROTOTYPES */
void strConcatenate(char *cDestinationStr, char *cSourceStr);
void removeNewline(char *cInputStr);

/** MAIN PROGRAM */
/*
 * main: Concatenates two strings using the pointer version of strcat
 *	 and prints the resulting string.
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

	strConcatenate(cFirstStr, cSecondStr);
	printf("The concatenated string is: %s\n", cFirstStr);

	return 0;
} /* End main() */

/*
 * strConcatenate	: Concatenates source string to the end of destination string
 *			  using pointers.
 * Input		: cDestinationStr (pointer to destination string)
 *			  cSourceStr (pointer to source string to append)
 * Author		: Dhruv Ajudiya
 * Created		: 7 October 2024
 * Modified		: 7 October 2024
 */
void strConcatenate(char *cDestinationStr, char *cSourceStr)
{
	while (*cDestinationStr != '\0')
		cDestinationStr++;

	while (*cSourceStr != '\0')
		*cDestinationStr++ = *cSourceStr++;

	*cDestinationStr = '\0';
} /* End strConcatenate() */

/*
 * removeNewline	: Removes the newline character from the end of a string
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
