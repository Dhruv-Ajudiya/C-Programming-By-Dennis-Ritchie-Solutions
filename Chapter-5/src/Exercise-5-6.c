/*
 *
 *
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */

/** REQUIRED HEADER FILES */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/** MACRO DEFINITIONS */
#define MAX_OP_SIZE		100	/* Maximum size of operand or operator */
#define IS_NUMBER		'0'	/* Signal that a number was found */
#define MAX_STACK_SIZE		10	/* Maximum size of the value stack */
#define BUFFER_SIZE		100	/* Size of buffer for pushed back input */

/** GLOBAL VARIABLES */
double dStackValue[MAX_STACK_SIZE];	/* Array to store values in stack */
int iStackPointer;			/* Next free position in the stack */
char cInputBuffer[BUFFER_SIZE];		/* Buffer to store input pushed back into input */
int iBufferPosition;			/* Next free position in input buffer */

/** FUNCTION PROTOTYPES */
void reverseString(char *cInputStr);
int atoi(char *cInputStr);
void itoa(int iNumber, char *cOutputStr);
void pushToStack(double dValue);
double popFromStack(void);
int getCharacter(void);
void ungetCharacter(int iInputCharacter);
int getNextOp(char cInputString[]);
int getLine(char cLine[], int iMaxLen);
int strRightIndex(char cSourceString[], char cSearchString[]);

/** MAIN PROGRAM */
/* 
 * main: 
 *
 *
 */
int main(void)
{
	int iChoice;          /* Store user choice from menu */
	char str[MAX_OP_SIZE];/* Buffer for string input */
	int iNumber;          /* Store integer values */

	while (1) {
		printf("\n--- Function Test Menu ---\n");
		printf("1. Convert string to integer (atoi)\n");
		printf("2. Convert integer to string (itoa)\n");
		printf("3. Get next operator or operand (getNextOp)\n");
		printf("4. Get line input (getLine)\n");
		printf("5. Find rightmost occurrence of substring (strRightIndex)\n");
		printf("0. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &iChoice);

		switch (iChoice) {
		case 1:
			printf("Enter a number: ");
			scanf("%s", str);
			iNumber = atoi(str);
			printf("Converted integer: %d\n", iNumber);
			break;

		case 2:
			printf("Enter an integer: ");
			if (scanf("%d", &iNumber) != 1) {
				printf("Error: Enter valid input\n");
				return 1;
			}
			itoa(iNumber, str);
			printf("Converted string: %s\n", str);
			break;

		case 3:
			{
			int iOpType;			/* Stores the type of the operator or operand */
			double dSecondOperand;		/* Stores the second operand for binary operations */
			char cInputString[MAX_OP_SIZE];	/* Array to store the current operator or operand as a string */

			printf("Use Reverse Polish Notation to enter the value\n"
					"enter '+' for addition\n"
					"enter '-' for subtraction\n"
					"enter '*' for multiplication\n"
					"enter '/' for division\n"
					"enter '%%' for modulus\n"
					"enter 'Q' to quit the calculator\n"
					"----------------------------------------------\n");
			while ((iOpType = getNextOp(cInputString)) != '\n') {
			switch (iOpType) {
				case IS_NUMBER:
					pushToStack(atof(cInputString));
					break;
				case '+':
					pushToStack(popFromStack() + popFromStack());
					break;
				case '*':
					pushToStack(popFromStack() * popFromStack());
					break;
				case '-':
					dSecondOperand = popFromStack();
					pushToStack(popFromStack() - dSecondOperand);
					break;
				case '/':
					dSecondOperand = popFromStack();
					if (dSecondOperand != 0.0)
						pushToStack(popFromStack() / dSecondOperand);
					else
						printf("Error: Division by zero is undefined\n");
					break;
				case '%':
					dSecondOperand = popFromStack();
					if (dSecondOperand != 0.0)
						pushToStack((int)popFromStack() % (int)dSecondOperand);
					else
						printf("Error: Division by zero is undefined\n");
					break;
				case '\n':
					printf("Result: %.8g\n", popFromStack());
					break;
				case 'Q':
					break;
				default:
					printf("Error: Unknown command %s\n", cInputString);
					break;
				}
			}
			break;

		case 4:
			printf("Enter a line of text: ");
			getchar(); /* Clear newline from buffer */
			iNumber = getLine(str, MAX_OP_SIZE);
			printf("Read line: %s\nLength: %d\n", str, iNumber);
			break;

		case 5:
			printf("Enter source string: ");
			scanf("%s", str);
			char pattern[MAX_OP_SIZE];
			printf("Enter search string: ");
			scanf("%s", pattern);
			iNumber = strRightIndex(str, pattern);
			if (iNumber >= 0)
				printf("Rightmost occurrence at index: %d\n", iNumber);
			else
				printf("Substring not found.\n");
			break;

		case 0:
			printf("Exiting program.\n");
			return 0;

		default:
			printf("Invalid choice. Please select a valid option.\n");
			break;
		}
	}

	return 0;
} /* End main() */

/*
 * atoi		: Converts a string of digits to an integer.
 * Input	: cInputStr (pointer to the string to convert)
 * Return	: Integer representation of the string
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int atoi(char *cInputStr)
{
	int iNumber = 0;	/* Stores the resulting integer */
	int iSign = 1;		/* Stores the sign of the integer */

	for (; isspace(*cInputStr); cInputStr++) /* Skip white space */ 
		;

	iSign = (*cInputStr == '-') ? -1 : 1;
	if (*cInputStr == '+' || *cInputStr == '-')
		cInputStr++;

	if (!isdigit(*cInputStr))
		return -1; /* Invalid input */

	for (iNumber = 0; isdigit(*cInputStr); cInputStr++)
		iNumber = (10 * iNumber) + *cInputStr - '0';

	return iSign * iNumber;
} /* End atoi() */

/*
 * itoa		: Converts an integer to a string representation.
 * Input	: iNumber (integer to convert)
 *		  cOutputStr (pointer to output buffer to store the string)
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void itoa(int iNumber, char *cOutputStr)
{
	int iSign = 1;			/* Store the sign of the integer */
	char *cTemp = cOutputStr;	/* Pointer to traverse and store characters */

	if (iNumber == 0) {
		*cTemp++ = '0';
		*cTemp = '\0';
		return ;
	}

	if (iNumber < 0) {
		iSign = -1;
		iNumber = -iNumber;
	}
	
	while (iNumber) {
		(*cTemp++) = iNumber % 10 + '0';
		iNumber /= 10;
	}
	if (iSign < 0)
		*cTemp++ = '-';
	*cTemp = '\0';
	
	reverseString(cOutputStr);
}

/*
 * reverseString	: Reverses a given string in place.
 * Input		: cInputStr (pointer to the string to reverse)
 * Author		: Dhruv Ajudiya
 * Created		: 28 October 2024
 * Modified		: 28 October 2024
 */
void reverseString(char *cInputStr)
{
	char *cEnd;	/* Points to the end of the string */
	char cTemp;	/* Temporary storage for swapping characters */

	cEnd = cInputStr + strlen(cInputStr) - 1;
	while (cInputStr < cEnd) {
		cTemp = *cInputStr;
		*cInputStr++ = *cEnd;
		*cEnd-- = cTemp;
	}
} /* End reverseString() */

/*
 * getNextOp	: Retrieves the next operator or numeric operand
 * Input	: cInputString (pointer to array to store the operator or operand)
 * Return	: The type of the operator or IS_NUMBER if a number was found
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getNextOp(char *cInputString)
{
	int iInputCharacter;	/* Store the current character read from input */

	/* Skip spaces and tabs */
	while ((*cInputString = iInputCharacter = getCharacter()) == ' ' || iInputCharacter == '\t')
		;
	*(cInputString + 1) = '\0';

	if (!isdigit(iInputCharacter) && iInputCharacter != '.' && iInputCharacter != '-')
		return iInputCharacter; /* Not a number */

	/* Handle possible negative number */
	if (iInputCharacter == '-') {
		iInputCharacter = getCharacter();
		if (!isdigit(iInputCharacter)) {
			/* If the next character is not a digit, it's a minus operator, not a negative number */
			if (iInputCharacter != EOF)
				ungetCharacter(iInputCharacter);
			return '-';
		} else {
			*cInputString = '-';  /* Negative number */
			*cInputString++ = iInputCharacter;
		}
	}

	/* Collect integer part */
	if (isdigit(iInputCharacter)) {
		while (isdigit(*cInputString++ = iInputCharacter = getCharacter()))
			;
	}
	/* Collect fractional part */
	if (iInputCharacter == '.') {
		while (isdigit(*cInputString++ = iInputCharacter = getCharacter()))
			;
	}
	*cInputString = '\0';

	if (iInputCharacter != EOF)
		ungetCharacter(iInputCharacter);

	return IS_NUMBER;
} /* End getNextOp() */

/*
 * strRightIndex	: Returns the position of the rightmost occurrence of pattern(cSearchString)
 *			  in input(cSourceString) string
 * Input		: cSourceString (the string to search in)
 *			  cSearchString (the pattern to search for)
 * Return		: Index of the rightmost occurrence of the pattern in string, or -1 if not found
 * Author		: Dhruv Ajudiya
 * Created		: 28 October 2024
 * Modified		: 28 October 2024
 */
int strRightIndex(char *cSourceString, char *cSearchString)
{
	char *cSourceTemp = cSourceString;	/* Pointer to the start of the source string */
	char *cSearchTemp;			/* Temporary pointer to traverse search string */
	char *cTemp;				/* Temporary pointer to traverse source string */

	for (; *cSourceString != '\0'; cSourceString++) {
		for (cTemp = cSourceString, cSearchTemp = cSearchString; *cSearchTemp != '\0' && tolower(*cTemp)
				== tolower(*cSearchTemp); cTemp++, cSearchTemp++)
			;

		if (*cSearchTemp == '\0')
			return cSourceString - cSourceTemp;
	}

	return -1;
} /* End strRightIndex() */

/*
 * getLine	: Reads a line from the console
 * Input	: cLine (character array to store the input line)
 *		  iMaxLen (maximum length of the line that can be stored)
 * Return	: Length of the input line
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getLine(char *cLine, int iMaxLen)
{
	int iInputChar;		/* Store the input character from user */
	char *cTemp = cLine;	/* Pointer to traverse and store characters */

	while (--iMaxLen > 0 && (iInputChar = getchar()) != EOF && iInputChar != '\n')
		*cLine++ = iInputChar;

	if (iInputChar == '\n')
		cLine++;
	*cLine = '\0';

	return cLine - cTemp; /* Length of the string */
} /* End getLine() */

/*
 * pushToStack	: Pushes a value onto the stack
 * Input	: dValue (value to push onto the stack)
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void pushToStack(double dValue)
{
	if (iStackPointer < MAX_STACK_SIZE)
		dStackValue[iStackPointer++] = dValue;
	else
		printf("Error: Stack full, cannot push %g\n", dValue);
} /* End pushToStack() */

/*
 * popFromStack	: Pops and returns the top value from the stack.
 * Return	: The top value from the stack, or 0.0 if the stack is empty
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
double popFromStack(void)
{
	if (iStackPointer > 0) {
		return dStackValue[--iStackPointer];
	} else {
		printf("Error: Stack empty, cannot pop value\n");
		return 0.0;
	}
} /* End popFromStack() */

/*
 * getCharacter	: Gets a (possibly pushed-back) character from input
 * Return	: The character read from input
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getCharacter(void)
{
	return (iBufferPosition > 0) ? cInputBuffer[--iBufferPosition] : getchar();
} /* End getCharacter() */

/*
 * ungetCharacter	: Pushes a character back into the input buffer
 * Input		: iInputCharacter (the character to push back)
 * Author		: Dhruv Ajudiya
 * Created		: 28 October 2024
 * Modified		: 28 October 2024
 */
void ungetCharacter(int iInputCharacter)
{
	if (iBufferPosition >= BUFFER_SIZE)
		printf("Error: Input buffer overflow\n");
	else
		cInputBuffer[iBufferPosition++] = iInputCharacter;
} /* End ungetCharacter() */
