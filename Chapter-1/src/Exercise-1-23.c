/*
 * This Program removes all comments from a C program. It handles quoted strings
 * and character constants properly.
 * Author	: Dhruv Ajudiya
 * Created	: 16 August 2024
 * Modified	: 16 August 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** REQUIRED MACROS */
#define IN_COMMENT	1	/* Inside a comment */
#define OUT_COMMENT	0	/* Outside a comment */
#define MAXLENGTH	1000	/* Size of the buffer array */

/** MAIN PROGRAM */
/*
 * main: Reads input from user and removes all comments from the input,
 *	 and outputs the result to console.
 */
int main(void)
{
	int iInputChar;				/* Current input character */
	int iTempChar;				/* Store temporary character */
	int iBufferIndex = 0;			/* Index for buffer array */
	int iCommentState = OUT_COMMENT;	/* Flag to check whether inside or outside a comment */
	char cBuffer[MAXLENGTH];		/* Buffer array to store characters */

	while ((iInputChar = getchar()) != EOF) {
		if (iInputChar == '/' && iCommentState == OUT_COMMENT) {
			iTempChar = iInputChar;
			iInputChar = getchar();
			if (iInputChar == '*') {
				iCommentState = IN_COMMENT;
			} else {
				cBuffer[iBufferIndex++] = iTempChar;
				cBuffer[iBufferIndex++] = iInputChar;
			}
		} else if (iInputChar == '*' && iCommentState == IN_COMMENT) {
			iTempChar = iInputChar;
			iInputChar = getchar();
			if (iInputChar == '/')
				iCommentState = OUT_COMMENT;
		} else {
			if (iCommentState == OUT_COMMENT)
				cBuffer[iBufferIndex++] = iInputChar;
		}

		/* Handle buffer overflow */
		if (iBufferIndex == MAXLENGTH - 1) {
			cBuffer[iBufferIndex] = '\0';
			printf("%s", cBuffer);
			iBufferIndex = 0;
		}
	}

	cBuffer[iBufferIndex] = '\0';
	printf("%s", cBuffer);

	return 0;
} /* End main() */
