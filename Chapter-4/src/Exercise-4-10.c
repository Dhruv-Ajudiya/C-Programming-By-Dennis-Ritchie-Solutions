/*
 * This Program demonstrates a Reverse Polish Notation (RPN) calculator. It reads
 * input in RPN format using getLine() function, processes the arithmetic  operations,
 * and prints the result.
 * Author	: Dhruv Ajudiya
 * Created	: 28 August 2024
 * Modified	: 09 September 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/** MACRO DEFINITIONS */
#define MAX_OP_SIZE		100	/* Maximum size of operand or operator */
#define IS_NUMBER		'0'	/* Signal that a number was found */
#define MAX_STACK_SIZE		10	/* Maximum size of the value stack */
#define MAXLINE			1000	/* Maximum length of input line */

/** GLOBAL VARIABLES */
double dStackValue[MAX_STACK_SIZE];	/* Arrary to store value in stack */
int iStackPointer;			/* Next free position in the stack */
char cInputLine[MAXLINE];		/* Maximum size of the input line */
int iLineIndex;				/* Index variable to iterate in input line */

/** FUNCTION PROTOTYPES */
int getNextOp(char cInputString[]);
void pushToStack(double value);
double popFromStack(void);
int getLine(char cLine[], int iMaxLen);

/** MAIN PROGRAM */
/*
 * main: It takes input from user calling getLine() function then processes the
 *	 input in Reverse Polish Notation (RPN) format, process the arithmetic
 *	 operations and prints the result.
 */
int main(void)
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
		"enter 'q' to quit the calculator\n"
		"----------------------------------------------\n");
	while (getLine(cInputLine, MAXLINE) > 0) {
		iLineIndex = 0;
		while ((iOpType = getNextOp(cInputString)) != '\0') {
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
			case 'q':
				return 0;
			default:
				printf("Error: Unknown command %s\n", cInputString);
				break;
			}
		}
	}

	return 0;
} /* End main() */

/*
 * getNextOp	: Retrieves the next operator or numeric operand
 * Input	: cInputString (the array to store the operator or operand)
 * Return	: The type of the operator or IS_NUMBER if a number was found
 * Author	: Dhruv Ajudiya
 * Created	: 28 August 2024
 * Modified	: 09 September 2024
 */
int getNextOp(char cInputString[])
{
	int i = 0;			/* Index variable to iterate in loop */
	int iInputCharacter;		/* Store the current character read from input */

	/* Skip spaces and tabs */
	while ((iInputCharacter = cInputLine[iLineIndex++]) == ' ' || iInputCharacter == '\t')
		;

	/* Check if it is a number or a negative number */
	if (iInputCharacter == '-' && isdigit(cInputLine[iLineIndex])) {
		/* It is a negative number */
		cInputString[i++] = iInputCharacter;
		iInputCharacter = cInputLine[iLineIndex++];
	}

	if (isdigit(iInputCharacter) || iInputCharacter == '.') {
		cInputString[i++] = iInputCharacter;

		/* Collect integer part */
		while (isdigit(iInputCharacter = cInputLine[iLineIndex++]))
			cInputString[i++] = iInputCharacter;

		/* Collect fractional part if any */
		if (iInputCharacter == '.') {
			cInputString[i++] = iInputCharacter;
			while (isdigit(iInputCharacter = cInputLine[iLineIndex++]))
				cInputString[i++] = iInputCharacter;
		}
		cInputString[i] = '\0';

		if (iInputCharacter != EOF)
			iLineIndex--; /* Push back the last character that wasn't part of the number */

		return IS_NUMBER;
	}

	/* If it is not a number, return the character (operator) */
	return iInputCharacter;
} /* End getNextOp() */

/*
 * getLine	: Reads a line from the console
 * Input	: cLine (character array to store the input line)
 *		  iMaxLen (maximum length of the line that can be stored)
 * Return	: Length of the input line
 * Author	: Dhruv Ajudiya
 * Created	: 28 August 2024
 * Modified	: 28 August 2024
 */
int getLine(char cLine[], int iMaxLen)
{
	int iInputChar; /* Store the input character from user */
	int i;		/* Index variable to iterate in the loop */

	for (i = 0; i < iMaxLen - 1 && (iInputChar = getchar()) != EOF && iInputChar != '\n'; i++)
		cLine[i] = iInputChar;

	if (iInputChar == '\n') {
		cLine[i] = iInputChar;
		i++;
	}
	cLine[i] = '\0';

	return i; /* Length of the string */
} /* End getLine() */

/*
 * pushToStack	: Pushes a value onto the stack
 * Input	: dInputValue (value to push onto the stack)
 * Author	: Dhruv Ajudiya
 * Created	: 28 August 2024
 * Modified	: 28 August 2024
 */
void pushToStack(double dInputValue)
{
	if (iStackPointer < MAX_STACK_SIZE)
		dStackValue[iStackPointer++] = dInputValue;
	else
		printf("Error: Stack full, cannot push %g\n", dInputValue);
} /* End pushToStack() */

/*
 * popFromStack	: Pops and returns the top value from the stack.
 * Return	: The top value from the stack, or 0.0 if the stack is empty
 * Author	: Dhruv Ajudiya
 * Created	: 28 August 2024
 * Modified	: 28 August 2024
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
