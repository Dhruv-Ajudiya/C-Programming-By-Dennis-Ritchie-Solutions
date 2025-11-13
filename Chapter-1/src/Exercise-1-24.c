/*
 * This Program checks for rudimentary syntax errors like unbalanced parentheses,
 * brackets, and braces. It also checks for quotes, escape sequences and comments.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACROS */
#define IN_COMMENT	1	/* Inside a comment */
#define OUT_COMMENT	0	/* Outside a comment */

/** MAIN PROGRAM */
/*
 * main: It takes input from user and checks for unbalanced parentheses, brackets,
 *	 braces, quotes, escape sequences, and comments.
 */
int main(void)
{
	int iInputChar;				/* Current input character */
	int iCommentState = OUT_COMMENT;	/* Flag to check whether inside or outside a comment */
	int iCommentCount = 0;			/* Count of comment */
	int iParenCount = 0;			/* Count of parentheses */
	int iBraceCount = 0;			/* Count of braces */
	int iBracketCount = 0;			/* Count of brackets */
	int iDoubleQuoteCount = 0;		/* Count of double quotes */
	int iSingleQuoteCount = 0;		/* Count of single quotes */
	int iEscapeSequenceCount = 0;		/* Count of invalid escape sequences */

	printf("Enter the string (Press Ctrl+D to end input):\n");
	while ((iInputChar = getchar()) != EOF) {
		if (iInputChar == '/' && iCommentState == OUT_COMMENT) {
			iInputChar = getchar(); /* Check if next character is '*' */
			if (iInputChar == '*') {
				iCommentState = IN_COMMENT;
				iCommentCount++;
			}
		} else if (iInputChar == '*' && iCommentState == IN_COMMENT) {
			iInputChar = getchar(); /* Check if next charcter is '/' */
			if (iInputChar == '/') {
				iCommentState = OUT_COMMENT;
				iCommentCount--;
			}
		} else if (iCommentState == OUT_COMMENT) {
			if (iInputChar == '(') {
				iParenCount++;
			} else if (iInputChar == ')') {
				iParenCount--;
			} else if (iInputChar == '{') {
				iBraceCount++;
			} else if (iInputChar == '}') {
				iBraceCount--;
			} else if (iInputChar == '[') {
				iBracketCount++;
			} else if (iInputChar == ']') {
				iBracketCount--;
			} else if (iInputChar == '\"') {
				iDoubleQuoteCount++;
			} else if (iInputChar == '\'') {
				iSingleQuoteCount++;
			} else if (iInputChar == '\\') { /* Escape sequence */
				iInputChar = getchar();
				if (iInputChar != 'n' && iInputChar != 't' && iInputChar != 'b' &&
						iInputChar != '\"' && iInputChar != '\\') {
					iEscapeSequenceCount++;
				}
			}
		}
	}

	if (iParenCount != 0)
		printf("Error: Unmatched parentheses\n");
	if (iBraceCount != 0)
		printf("Error: Unmatched braces\n");
	if (iBracketCount != 0)
		printf("Error: Unmatched brackets\n");
	if (iDoubleQuoteCount % 2 != 0)
		printf("Error: Unmatched double quotes\n");
	if (iSingleQuoteCount % 2 != 0)
		printf("Error: Unmatched single quotes\n");
	if (iEscapeSequenceCount != 0)
		printf("Error: Invalid escape sequences\n");
	if (iCommentCount != 0)
		printf("Error: Unmatched comment block\n");

	printf("Syntax check completed\n");

	return 0;
} /* End main() */
