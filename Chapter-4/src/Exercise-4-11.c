/*
 * This Program demonstrates a Reverse Polish Notation (RPN) calculator. It reads
 * input in RPN format, processes the arithmetic  operations, and prints the result.
 * This program modifies the getNextOp() function such that it doesn't need the
 * ungetCharacter() function.
 * Author	: Dhruv Ajudiya
 * Created	: 29 August 2024
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
#define BUFFER_SIZE		100	/* Size of buffer for pushed back input */

/** GLOBAL VARIABLES */
double dStackValue[MAX_STACK_SIZE];	/* Arrary to store value in stack */
int iStackPointer;			/* Next free position in the stack */
char cInputBuffer[BUFFER_SIZE];		/* Buffer to store input pushed back into input */
int iBufferPosition;			/* Next free position in input buffer */

/** FUNCTION PROTOTYPES */
int getNextOp(char cInputString[]);
void pushToStack(double value);
double popFromStack(void);
int getCharacter(void);

/** MAIN PROGRAM */
/*
 * main: It takes input from user calling getNextOp() function then processes the
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
	while ((iOpType = getNextOp(cInputString)) != EOF) {
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

	return 0;
} /* End main() */

/*
 * getNextOp	: Retrieves the next operator or numeric operand
 * Input	: cInputString (the array to store the operator or operand)
 * Return	: The type of the operator or '0' if a number was found
 * Author	: Dhruv Ajudiya
 * Created	: 29 August 2024
 * Modified	: 09 September 2024
 */
int getNextOp(char cInputString[])
{
	int i = 0;		/* Index variable to iterate in loop */
	int iInputCharacter;	/* Store the current character read from input */
	int iNextChar;		/* Store the next input character */
	static int iLastChar;	/* Store the last input character */

	if (iLastChar == 0) {
		iInputCharacter = getCharacter();
	} else {
		iInputCharacter = iLastChar;
		iLastChar = 0;
	}

	/* Skip spaces and tabs */
	while (iInputCharacter == ' ' || iInputCharacter == '\t')
		iInputCharacter = getCharacter();

	/* Handle negative numbers */
	if (iInputCharacter == '-' && (isdigit(iNextChar = getCharacter()) || iNextChar == '.')) {
		/* It's a negative number */
		cInputString[i++] = '-';
		iInputCharacter = iNextChar;
	} else if (iInputCharacter == '-') {
		iLastChar = iNextChar;
		return '-';	/* It's an operator, return '-' */
	}

	if (isdigit(iInputCharacter) || iInputCharacter == '.') {
		cInputString[i++] = iInputCharacter;

		/* Collect integer part */
		while (isdigit(iInputCharacter = getCharacter()))
			cInputString[i++] = iInputCharacter;

		/* Collect fractional part, if any */
		if (iInputCharacter == '.') {
			cInputString[i++] = iInputCharacter;
			while (isdigit(iInputCharacter = getCharacter()))
				cInputString[i++] = iInputCharacter;
		}
		cInputString[i] = '\0';

		if (iInputCharacter != EOF)
			iLastChar = iInputCharacter;  /* Push back non-numeric character */

		return IS_NUMBER;  /* Return the signal that it's a number */
	}

	return iInputCharacter; /* Not a number, return the character */
} /* End getNextOp() */

/*
 * pushToStack	: Pushes a value onto the stack
 * Input	: dInputValue (value to push onto the stack)
 * Author	: Dhruv Ajudiya
 * Created	: 29 August 2024
 * Modified	: 29 August 2024
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
 * Created	: 29 August 2024
 * Modified	: 29 August 2024
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
 * Created	: 29 August 2024
 * Modified	: 29 August 2024
 */
int getCharacter(void)
{
	return (iBufferPosition > 0) ? cInputBuffer[--iBufferPosition] : getchar();
} /* End getCharacter() */
