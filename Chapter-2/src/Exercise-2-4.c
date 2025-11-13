/*
 * This program deletes each character in first string that matches any character
 * in second string.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <ctype.h>

/** REQUIRED MACRO */
#define MAXLENGTH	100	/* Maximum input line length */

/** FUNCTION PROTOTYPES */
void squeeze(char cFirstStr[], char cSecondStr[]);

/** MAIN PROGRAM */
/*
 * main: It reads two strings from the user and calls the squeeze() function
 *	 to remove characters from the first string that matches any charcter in the
 *	 second string.
 */
int main(void)
{
	char cFirstStr[MAXLENGTH];  /* Store the first string */
	char cSecondStr[MAXLENGTH]; /* Store the second string */

	printf("Enter the first string: ");
	scanf("%[^\n]%*c", cFirstStr);
	printf("Enter the second string: ");
	scanf("%[^\n]%*c", cSecondStr);
	squeeze(cFirstStr, cSecondStr);
	printf("Result after squeezing: %s\n", cFirstStr);

	return 0;
} /* End main() */

/*
 * squeeze	: Deletes each character in first string that matches any character in
 *		  second string
 * Input	: cFirstStr (an array containing the first string)
 *		  cSecondStr (an array containing the second string)
 * Output	: Modified first string with the matched characters removed
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */
void squeeze(char cFirstStr[], char cSecondStr[])
{
	int i;		/* Index variable for the first string */
	int j;		/* Index variable for the second string */
	int k = 0;	/* Index for the result placement in the first string */
	int iDelete;	/* Flag to determine if a character should be deleted */

	for (i = 0; cFirstStr[i] != '\0'; i++) {
		iDelete = 0;
		for (j = 0; cSecondStr[j] != '\0'; j++) {
			if (tolower(cFirstStr[i]) == tolower(cSecondStr[j])) {
				iDelete = 1;
				break;
			}
		}

		if (iDelete == 0)
			cFirstStr[k++] = cFirstStr[i];
	}

	cFirstStr[k] = '\0';
} /* End squeeze() */
