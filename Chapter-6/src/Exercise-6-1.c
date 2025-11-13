/*
 * This program reads input one character at a time to extract words,  
 * handles comments (both single-line and multi-line), string constants,  
 * and preprocessor directives by skipping over them.
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */

/** REQUIRED HEADER FILES */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/** STRUCTURE DEFINITIONS */
struct Key {
	char *word;
	int count;
} keytab[] = {
	{"auto", 0}, {"break", 0}, {"case", 0}, {"char", 0},
	{"const", 0}, {"continue", 0}, {"default", 0}, {"do", 0},
	{"double", 0}, {"else", 0}, {"enum", 0}, {"extern", 0},
	{"float", 0}, {"for", 0}, {"goto", 0}, {"if", 0},
	{"int", 0}, {"long", 0}, {"register", 0}, {"return", 0},
	{"short", 0}, {"signed", 0}, {"sizeof", 0}, {"static", 0},
	{"struct", 0}, {"switch", 0}, {"typedef", 0}, {"union", 0},
	{"unsigned", 0}, {"void", 0}, {"volatile", 0}, {"while", 0}
};

/** MACRO DEFINITIONS */
#define NKEYS		(sizeof(keytab) / sizeof(keytab[0]))	/* Total number of keywords */
#define MAX_WORD	100					/* Maximum length of a word */
#define BUFFER_SIZE	100					/* Size of buffer for pushed back input */

/** GLOBAL VARIABLES */
char cInputBuffer[BUFFER_SIZE];		/* Buffer to store input pushed back into input */
int iBufferPosition = 0;		/* Next free position in input buffer */

/** FUNCTION PROTOTYPES */
int getWord(char *cWordBuffer, int iMaxLength);
int binSearch(char *cWord, struct Key tab[], int iArraySize);
int getCharacter(void);
void ungetCharacter(int iInputCharacter);

/** MAIN PROGRAM */
/*
 * main: Reads input from the standard input (keyboard or file), processes it, and 
 *	 outputs the frequency of each keyword found in the input.
 */
int main(void)
{
	int iIndex;		/* Loop index for iterating over keywords */
	char cWord[MAX_WORD];	/* Buffer to store the current word */

	while (getWord(cWord, MAX_WORD) != EOF) {
		if (isalpha(cWord[0])) {
			if ((iIndex = binSearch(cWord, keytab, NKEYS)) >= 0) {
				keytab[iIndex].count++;
			}
		}
	}

	printf("Keyword occurrences:\n");
	for (iIndex = 0; iIndex < (int)NKEYS; iIndex++) {
		if (keytab[iIndex].count > 0) {
			printf("%4d %s\n", keytab[iIndex].count, keytab[iIndex].word);
		}
	}

	return 0;
} /* End main() */

/*
 * binSearch	: Perform a binary search on a sorted array of keys
 * Input	: cWord (word to search for)
 *		  tab (sorted array of struct Key)
 *		  iArraySize (number of elements in the array)
 * Return	: The index of the target word in the array, or -1 if not found
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */
int binSearch(char *cWord, struct Key tab[], int iArraySize)
{
	int iLowIndex = 0;			/* Lowest index of the array */
	int iHighIndex = iArraySize - 1;	/* Highest index of the array */
	int iMidIndex = 0;			/* Midpoint index of the array */

	while (iLowIndex <= iHighIndex) {
		iMidIndex = (iLowIndex + iHighIndex) / 2;

		if (strcmp(cWord, tab[iMidIndex].word) < 0) {
			iHighIndex = iMidIndex - 1;
		} else if (strcmp(cWord, tab[iMidIndex].word) > 0) {
			iLowIndex = iMidIndex + 1;
		} else {
			return iMidIndex;	/* Target word found */
		}
	}

	return -1;	/* Target word not found */
} /* End binSearch() */

/*
 * getWord	: Reads the next word or significant input token from input.
 * Input	: cWordBuffer (Buffer to store the read word)
 *		  iMaxLength (Maximum length of the word to read)
 * Return	: The first character of the word or EOF if end of input is reached
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */
int getWord(char *cWordBuffer, int iMaxLength)
{
	int iCurrentChar;			/* Current character being processed */
	int iNextChar;				/* Holds the next character for handling comments */
	char *cBuffPointer = cWordBuffer;	/* Pointer to traverse cWordBuffer */

	/* Skip any whitespace characters */
	while (isspace(iCurrentChar = getCharacter()))
		;

	if (iCurrentChar != EOF)
		*cBuffPointer++ = iCurrentChar;	/* Store the first non-space character */

	/* Handle non-alphabetic characters like comments, preprocessor, and strings */
	if (!isalpha(iCurrentChar)) {
		if (iCurrentChar == '\"') { /* Handle string constants */
			while ((iCurrentChar = getCharacter()) != EOF && iCurrentChar != '\"')
				;
		} else if (iCurrentChar == '#') { /* Handle preprocessor directives */
			while ((iCurrentChar = getCharacter()) != EOF && iCurrentChar != '\n')
				;
		} else if (iCurrentChar == '/') { /* Handle comments */
			iNextChar = getCharacter();
			if (iNextChar == '/') { /* Single-line comment */
				while ((iCurrentChar = getCharacter()) != EOF && iCurrentChar != '\n')
					;
			} else if (iNextChar == '*') { /* Multi-line comment */
				while ((iCurrentChar = getCharacter()) != EOF) {
					if (iCurrentChar == '*') {
						if ((iNextChar = getCharacter()) == '/')
							break;
						else
							ungetCharacter(iNextChar); /* Push back extra character */
					}
				}
			} else {
				ungetCharacter(iNextChar);  /* Not a comment, push back */
			}
		}
		*cBuffPointer = '\0';
		return iCurrentChar;
	}

	/* Read alphanumeric characters to form the word */
	for (; --iMaxLength > 0; cBuffPointer++) {
		if (!isalnum(*cBuffPointer = getCharacter())) {
			ungetCharacter(*cBuffPointer); /* Push back the non-alphanumeric character */
			break;
		}
	}
	*cBuffPointer = '\0';

	return cWordBuffer[0]; /* Return the first character of the word */
}

/*
 * getCharacter	: Gets a (possibly pushed-back) character from input
 * Return	: The character read from input
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */
int getCharacter(void)
{
	return (iBufferPosition > 0) ? cInputBuffer[--iBufferPosition] : getchar();
} /* End getCharacter() */

/*
 * ungetCharacter	: Pushes a character back into the input buffer
 * Input		: iInputCharacter (the character to push back)
 * Author		: Dhruv Ajudiya
 * Created		: 27 November 2024
 * Modified		: 27 November 2024
 */
void ungetCharacter(int iInputCharacter)
{
	if (iBufferPosition >= BUFFER_SIZE)
		printf("Error: Input buffer overflow\n");
	else
		cInputBuffer[iBufferPosition++] = iInputCharacter;
} /* End ungetCharacter() */
