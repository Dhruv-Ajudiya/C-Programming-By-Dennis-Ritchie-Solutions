/*
 * This program demonstrates the usage of custom implementations of strncpy,
 * strncat, and strncmp functions using pointers.
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
void strnCpy(char *cDestinationStr, char *cSourceStr, int iSize);
void strnCat(char *cDestinationStr, char *cSourceStr, int iSize);
int strnCmp(const char *cString1, const char *cString2, int iSize);
void removeNewline(char *cInputStr);


/** MAIN PROGRAM */
/*
 * main: Reads two strings from the user and demonstrates the use of strnCpy,
 *	 strnCat, and strnCmp functions.
 */
int main(void)
{
	char cFirstStr[MAXSTRINGSIZE];	/* Store first input string */
	char cSecondStr[MAXSTRINGSIZE];	/* Store second input string */
	int iChoice;			/* Store the choice of the user */
	int iSize;			/* Store the size limit for operation */

	printf("Enter the first string: ");
	fgets(cFirstStr, MAXSTRINGSIZE, stdin);
	removeNewline(cFirstStr);

	printf("Enter the second string: ");
	fgets(cSecondStr, MAXSTRINGSIZE, stdin);
	removeNewline(cSecondStr);

	printf("\nChoose an operation to perform:\n");
	printf("1. Copy second string to first\n");
	printf("2. Concatenate second string to first\n");
	printf("3. Compare first and second strings\n");
	printf("Enter your choice: ");
	scanf("%d", &iChoice);
	
	printf("Enter the size limit for the operation: ");
	scanf("%d", &iSize);

	switch (iChoice) {
	case 1:
		strnCpy(cFirstStr, cSecondStr, iSize);
		printf("After copy: %s\n", cFirstStr);
		break;
	case 2:
		strnCat(cFirstStr, cSecondStr, iSize);
		printf("After concatenation: %s\n", cFirstStr);
		break;
	case 3:
		if (strnCmp(cFirstStr, cSecondStr, iSize) == 0)
			printf("String match found\n");
		else
			printf("Match not found\n");
		break;
	default:
		printf("Invalid choice.\n");
	}

	return 0;
} /* End main() */

/*
 * strnCpy	: Copies up to given length of characters from source to destination.
 * Input	: cDestinationStr (pointer to the destination string)
 *		  cSourceStr (pointer to the source string)
 *		  iSize (number of characters to copy)
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */
void strnCpy(char *cDestinationStr, char *cSourceStr, int iSize)
{
	int i;	/* Index variable to iterate in the loop */

	for (i = 0; i < iSize && *cSourceStr != '\0'; i++)
		*cDestinationStr++ = *cSourceStr++;

	for (; i < iSize; i++)
		*cDestinationStr++ = '\0';

} /* End strnCpy() */

/*
 * strnCat	: Concatenates up to given length of characters from source to the end of
 *		  the destination string.
 * Input	: cDestinationStr (pointer to the destination string)
 *		  cSourceStr (pointer to the source string)
 *		  iSize (number of characters to concatenate)
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */
void strnCat(char *cDestinationStr, char *cSourceStr, int iSize)
{
	int i;	/* Index variable to iterate in the loop */

	while (*cDestinationStr != '\0')
		cDestinationStr++;

	for (i = 0; i < iSize && *cSourceStr != '\0'; i++)
		*cDestinationStr++ = *cSourceStr++;

	*cDestinationStr = '\0';
} /* End strnCat() */

/*
 * strnCmp	: Compares up to given length of characters of two strings.
 * Input	: cString1 (pointer to the first string)
 *		  cString2 (pointer to the second string)
 *		  iSize (number of characters to compare)
 * Return	: 0 if both strings are equal in the first given length of characters
 *		  Positive if cString1 > cString2
 *		  Negative if cString1 < cString2
 * Author	: Dhruv Ajudiya
 * Created	: 7 October 2024
 * Modified	: 7 October 2024
 */
int strnCmp(const char *cString1, const char *cString2, int iSize)
{
	int i;	/* Index variable to iterate in the loop */

	for (i = 0; i < iSize; i++) {	
		if (*cString1 != *cString2)
			return *cString1 - *cString2;

		if (*cString1 != '\0' || *cString2 != '\0')
			break;

		cString1++;
		cString2++;
	}

	return 0;
} /* End strnCmp() */

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
