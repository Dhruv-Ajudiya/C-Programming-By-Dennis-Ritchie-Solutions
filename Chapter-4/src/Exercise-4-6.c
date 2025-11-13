/*
 * This Program demonstrates an extended Reverse Polish Notation (RPN) calculator.
 * It supports basic arithmetic operations, handles variables with single-letter names,
 * and stores the value assigned to that variable and prints the stored variables.
 * Author	: Dhruv Ajudiya
 * Created	: 27 August 2024
 * Modified	: 27 August 2024
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
#define VARIABLES_COUNT		26	/* Number of single letter variables */

/** GLOBAL VARIABLES */
double dStackValue[MAX_STACK_SIZE];	/* Array to store values in stack */
int iStackPointer;			/* Next free position in the stack */
char cInputBuffer[BUFFER_SIZE];		/* Buffer to store input pushed back into input */
int iBufferPosition;			/* Next free position in input buffer */

/** FUNCTION PROTOTYPES */
int getNextOp(char cInputString[]);
void pushToStack(double value);
double popFromStack(void);
int getCharacter(void);
void ungetCharacter(int iInputCharacter);

/** MAIN PROGRAM */
/*
 * main: It takes input from user calling getNextOp() function then processes the
 *	 input in Reverse Polish Notation (RPN) format, performs the arithmetic
 *	 operations, and prints the result. It handles variables with single-letter
 *	 names, and stores the value assigned to that variable and prints the stored variables.
 */
int main(void)
{
	int iOpType;					/* Store the type of the operator or operand */
	double dSecondOperand;				/* Store the second operand for binary operations */
	char cInputString[MAX_OP_SIZE];			/* Array to store the current operator or operand as a string */
	double dTempValue;				/* Store the temporary value */
	double dVariables[VARIABLES_COUNT] = {0};	/* Array to store single-letter variables */
	int iLastVariable = 0;				/* Store the last variable name used */
	double dLastPrintedValue = 0;			/* Store the last printed value */
	int i;						/* Index variable to iterate in loop */

	printf("Use Reverse Polish Notation to enter the value\n"
		"enter '+' for addition\n"
		"enter '-' for subtraction\n"
		"enter '*' for multiplication\n"
		"enter '/' for division\n"
		"enter a single letter to use a variable (A-Z)\n"
		"enter '=' to assign a value to a variable\n"
		"enter 'l' to print the last printed value\n"
		"enter 'p' to print all variables stored\n"
		"enter 'q' to quit the calculator\n"
		"----------------------------------------------\n");

	while ((iOpType = getNextOp(cInputString)) != EOF) {
		switch (iOpType) {
		case IS_NUMBER:
			pushToStack(atof(cInputString));
			break;
		case '+':
			dTempValue = popFromStack() + popFromStack();
			pushToStack(dTempValue);
			printf("Addition: %.8g\n", dTempValue);
			dLastPrintedValue = dTempValue;
			break;
		case '*':
			dTempValue = popFromStack() * popFromStack();
			pushToStack(dTempValue);
			printf("Multiplication: %.8g\n", dTempValue);
			dLastPrintedValue = dTempValue;
			break;
		case '-':
			dSecondOperand = popFromStack();
			dTempValue = popFromStack() - dSecondOperand;
			pushToStack(dTempValue);
			printf("Subtraction: %.8g\n", dTempValue);
			dLastPrintedValue = dTempValue;
			break;
		case '/':
			dSecondOperand = popFromStack();
			if (dSecondOperand != 0.0) {
				dTempValue = popFromStack() / dSecondOperand;
				pushToStack(dTempValue);
				printf("Division: %.8g\n", dTempValue);
				dLastPrintedValue = dTempValue;
			} else {
				printf("Error: Division by zero is undefined\n");
			}
			break;

		/* Assign the values to the variables */
		case '=':
			popFromStack();
			if (iLastVariable >= 'A' && iLastVariable <= 'Z')
				dVariables[iLastVariable - 'A'] = popFromStack();
			else
				printf("Error: Invalid variable name\n");
			break;

		/* Print all stored variables */
		case 'p':
			printf("Stored variables:\n");
			for (i = 0; i < VARIABLES_COUNT; i++) {
				if (dVariables[i] != 0)
					printf("%c = %.8g\n", 'A' + i, dVariables[i]);
			}
			break;

		/* Case to print the last printed value */
		case 'l':
			printf("Last printed value: %.8g\n", dLastPrintedValue);
			break;

		case '\n':
			if (iStackPointer <= 0)
				printf("Error: Stack empty\n");
			break;
		case 'q':
			return 0;
		default:
			if (iOpType >= 'A' && iOpType <= 'Z') {
				pushToStack(dVariables[iOpType - 'A']);
				iLastVariable = iOpType;	/* Store the variable for '=' operation */
			} else {
				printf("Error: Unknown command %s\n", cInputString);
			}
			break;
		}
	}

	return 0;
} /* End main() */

/*
 * getNextOp	: Retrieves the next operator or numeric operand
 * Input	: cInputString (the array to store the operator or operand)
 * Return	: The type of the operator or IS_NUMBER if a number was found
 * Author	: Dhruv Ajudiya
 * Created	: 27 August 2024
 * Modified	: 27 August 2024
 */
int getNextOp(char cInputString[])
{
	int i;			/* Index variable to iterate in loop */
	int iInputCharacter;	/* Store the current character read from input */

	/* Skip spaces and tabs */
	while ((cInputString[0] = iInputCharacter = getCharacter()) == ' ' || iInputCharacter == '\t')
		;
	cInputString[1] = '\0';

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
			cInputString[0] = '-';  /* Negative number */
			cInputString[1] = iInputCharacter;
			i = 1;
		}
	} else {
		i = 0; /* Positive number */
	}

	/* Collect integer part */
	if (isdigit(iInputCharacter)) {
		while (isdigit(cInputString[++i] = iInputCharacter = getCharacter()))
			;
	}
	/* Collect fractional part */
	if (iInputCharacter == '.') {
		while (isdigit(cInputString[++i] = iInputCharacter = getCharacter()))
			;
	}
	cInputString[i] = '\0';

	if (iInputCharacter != EOF)
		ungetCharacter(iInputCharacter);

	return IS_NUMBER;
} /* End getNextOp() */

/*
 * pushToStack	: Pushes a value onto the stack
 * Input	: dValue (value to push onto the stack)
 * Author	: Dhruv Ajudiya
 * Created	: 27 August 2024
 * Modified	: 27 August 2024
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
 * Created	: 27 August 2024
 * Modified	: 27 August 2024
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
 * Created	: 27 August 2024
 * Modified	: 27 August 2024
 */
int getCharacter(void)
{
	return (iBufferPosition > 0) ? cInputBuffer[--iBufferPosition] : getchar();
} /* End getCharacter() */

/*
 * ungetCharacter	: Pushes a character back into the input buffer
 * Input		: iInputCharacter (the character to push back)
 * Author		: Dhruv Ajudiya
 * Created		: 27 August 2024
 * Modified		: 27 August 2024
 */
void ungetCharacter(int iInputCharacter)
{
	if (iBufferPosition >= BUFFER_SIZE)
		printf("Error: Input buffer overflow\n");
	else
		cInputBuffer[iBufferPosition++] = iInputCharacter;
} /* End ungetCharacter() */
