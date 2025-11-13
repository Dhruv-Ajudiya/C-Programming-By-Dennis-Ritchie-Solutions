/*
 * This program evaluates a Reverse Polish Notation (RPN) expression provided as
 * command-line arguments. Each operator or operand is passed as a separate argument,
 * allowing the user to perform arithmetic operations in RPN format. The program
 * supports addition, subtraction, multiplication, division, and modulus.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 Octoer 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/** MACRO DEFINITIONS */
#define IS_NUMBER		'0'	/* Signal that a number was found */
#define MAX_STACK_SIZE		10	/* Maximum size of the value stack */

/** GLOBAL VARIABLES */
double dStackValue[MAX_STACK_SIZE];	/* Arrary to store value in stack */
int iStackPointer;			/* Next free position in the stack */

/** FUNCTION PROTOTYPES */
int getNextOp(char cInputString[]);
void pushToStack(double value);
double popFromStack(void);

/** MAIN PROGRAM */
/*
 * main: Processes command-line arguments in Reverse Polish Notation (RPN) format,
 *	 evaluates arithmetic expressions, and displays the result of each operation.
 */
int main(int argc, char *argv[])
{
	int iOpType;			/* Store the type of the operator or operand */
	double dSecondOperand;		/* Store the second operand for binary operations */
	double dTempValue;		/* Store the temporary value */

	if(argc == 1){
		printf("Usage: expr num1 num2 [num3 ..] oper1 [oper2 ...]\n");
		return -1;
	} else {
		while (--argc > 0) {
			iOpType = getNextOp(*++argv);
			switch (iOpType) {
			case IS_NUMBER:
				pushToStack(atof(*argv));
				break;
			case '+':
				dTempValue = popFromStack() + popFromStack();
				pushToStack(dTempValue);
				break;
			case '*':
				dTempValue = popFromStack() * popFromStack();
				pushToStack(dTempValue);
				break;
			case '-':
				dSecondOperand = popFromStack();
				dTempValue = popFromStack() - dSecondOperand;
				pushToStack(dTempValue);
				break;
			case '/':
				dSecondOperand = popFromStack();
				if (dSecondOperand != 0.0) {
					dTempValue = popFromStack() / dSecondOperand;
					pushToStack(dTempValue);
				} else {
					printf("Error: Division by zero is undefined\n");
				}
				break;
			case '%':
				dSecondOperand = popFromStack();
				if (dSecondOperand != 0.0) {
					dTempValue = (int)popFromStack() % (int)dSecondOperand;
					pushToStack(dTempValue);
				} else {
					printf("Error: Division by zero is undefined\n");
				}
				break;
			default:
				printf("Error: Unknown argument %s\n", *argv);
				break;
			}
		}
	}
	printf("Final result: %.8g\n", popFromStack());
	return 0;
} /* End main() */

/*
 * getNextOp	: Determines if the argument is a number or an operator
 * Input	: cInputString (a pointer to the character array representing the operand or operator)
 * Return	: The type of the operator or IS_NUMBER if a number was found
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getNextOp(char *cInputString)
{
	int iCurrentChar = *cInputString; /* Holds the current character in inputString */

	if (iCurrentChar == '-' && isdigit(*(cInputString + 1)))
		cInputString++;

	while (isdigit(iCurrentChar = *cInputString++) || iCurrentChar == '.')
		;

	if (iCurrentChar == '\0')
		return IS_NUMBER;
	else
		return iCurrentChar;
} /* End getNextOp() */

/*
 * pushToStack	: Pushes a value onto the stack
 * Input	: dInputValue (value to push onto the stack)
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
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
