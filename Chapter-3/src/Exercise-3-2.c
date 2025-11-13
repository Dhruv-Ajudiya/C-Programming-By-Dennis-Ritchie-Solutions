/*
 * This program converts characters like newline and tab into visible sequences
 * like '\n' and '\t'. It also converts the escape sequences into real characters.
 * Author	: Dhruv Ajudiya
 * Created	: 21 August 2024
 * Modified	: 21 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACRO */
#define MAXLENGTH	100	/* Maximum length of the array */

/** FUNCTION PROTOTYPE */
void convertEscapeSequence(char cEscapedString[], char cOriginalString[]);
void restoreEscapeSequence(char cOriginalString[], char cEscapedString[]);

/** MAIN PROGRAM */
/*
 * main: It takes string as a input from the user, converts the string to escape sequences
 *	 by calling convertEscapeSequence() function and then converts it back to the original
 *	 form by calling restoreEscapeSequence() function then displays both results on the console.
 */
int main(void)
{
	char cOriginalString[MAXLENGTH];	/* Original user input string */
	char cEscapedString[MAXLENGTH];		/* String with escape sequences */
	char cRestoredString[MAXLENGTH];	/* String restored from escape sequences */
	int iInputChar;				/* Store the input character from user */
	int i = 0;				/* Index variable to iterate in loop*/

	printf("Enter the string (Press Ctrl + D to end input):\n");
	while ((iInputChar = getchar()) != EOF) {
		cOriginalString[i] = iInputChar;
		i++;
	}
	cOriginalString[i] = '\0';
	convertEscapeSequence(cEscapedString, cOriginalString);
	printf("\nString with escape sequences:\n%s\n", cEscapedString);

	restoreEscapeSequence(cRestoredString, cEscapedString);
	printf("\nRestored original string:\n%s\n", cRestoredString);

	return 0;
} /* End main() */

/*
 * convertEscapeSequence	: Converts special characters in the original string
 *				  (like newline, tab) into visible escape sequences
 *				  (like \n, \t) and stores the result in cEscapedString
 * Input			: cOriginalString (string to be converted)
 *				  cEscapedString (contains the converted string)
 * Output			: cEscapedString (contains the converted string)
 */
void convertEscapeSequence(char cEscapedString[], char cOriginalString[])
{
	int i = 0;	/* Index for cOriginalString */
	int j = 0;	/* Index for cEscapedString */

	while (cOriginalString[i] != '\0') {
		switch (cOriginalString[i]) {
		case '\t':
			cEscapedString[j++] = '\\';
			cEscapedString[j] = 't';
			break;

		case '\n':
			cEscapedString[j++] = '\\';
			cEscapedString[j] = 'n';
			break;

		case '\"':
			cEscapedString[j++] = '\\';
			cEscapedString[j] = '"';
			break;

		case '\'':
			cEscapedString[j++] = '\\';
			cEscapedString[j] = '\'';
			break;

		case '\\':
			cEscapedString[j++] = '\\';
			cEscapedString[j] = '\\';
			break;

		default:
			cEscapedString[j] = cOriginalString[i];
			break;
		}
		i++;
		j++;
	}

	cEscapedString[j] = '\0';
} /* End convertEscapeSequence() */

/*
 * restoreEscapeSequence	: Converts escape sequences in the convertEscapeSequenced string
 *				  (like \n, \t) back to the actual special characters (like newline,
 *				  tab) and stores the result in cRestoredString.
 * Input			: cOriginalString (string to be converted)
 *				  cRestoredString (result string)
 * Output			: cRestoredString (contains the restored string)
 */
void restoreEscapeSequence(char cRestoredString[], char cOriginalString[])
{
	int i = 0;	/* Index for cOriginalString */
	int j = 0;	/* Index for cRestoredString */

	while (cOriginalString[i] != '\0') {
		if (cOriginalString[i] == '\\') {
			i++;
			switch (cOriginalString[i]) {
			case 't':
				cRestoredString[j] = '\t';
				break;

			case 'n':
				cRestoredString[j] = '\n';
				break;

			case '"':
				cRestoredString[j] = '\"';
				break;

			case '\'':
				cRestoredString[j] = '\'';
				break;

			case '\\':
				cRestoredString[j] = '\\';
				break;

			default:
				cRestoredString[j++] = '\\';
				cRestoredString[j] = cOriginalString[i];
				break;
			}
		} else {
			cRestoredString[j] = cOriginalString[i];
		}
		i++;
		j++;
	}

	cRestoredString[j] = '\0';
} /* End restoreEscapeSequence() */
