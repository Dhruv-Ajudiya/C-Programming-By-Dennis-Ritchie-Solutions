/*
 * Implementation of the 'tail' command that prints the last n lines of input.
 * Supports a command-line argument '-n' to specify the number of lines to display.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** MACRO DEFINITIONS */
#define MAXLINES  1000  /* Maximum number of lines to store */
#define MAXLEN    1000  /* Maximum length of a single line */
#define ALLOCSIZE 10000 /* Size of memory allocation buffer */

/** GLOBAL VARIABLES */
char *lineptr[MAXLINES];          /* Array of pointers to lines */
static char allocbuf[ALLOCSIZE]; /* Storage for alloc() */
static char *allocp = allocbuf;  /* Next free position in allocbuf */

/** FUNCTION PROTOTYPES */
void strCpy(char *dest, const char *src);
int getLine(char s[], int lim);
char *alloc(int n);
int readLines(char *lineptr[]);

/** FUNCTION DEFINITIONS */
/*
 * strCpy	: Copies the string `src` to `dest`.
 * Input	: dest (destination string), src (source string)
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void strCpy(char *dest, const char *src) {
	while ((*dest++ = *src++) != '\0')
		;
}

/*
 * getLine	: Reads a line of input and stores it in the array `s`.
 * Input	: s (character array to store the line), lim (maximum length)
 * Output	: Length of the line read
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getLine(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/*
 * alloc	: Allocates `n` bytes of memory and returns a pointer to it.
 * Input	: n (number of bytes to allocate)
 * Output	: Pointer to the allocated memory, or NULL if insufficient space
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else {
		return NULL;
	}
}

/*
 * readLines	: Reads input lines and stores pointers to them in `lineptr`.
 * Input	: lineptr (array of pointers to store lines)
 * Output	: Number of lines read, or -1 on error
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int readLines(char *lineptr[]) {
	int len, nlines = 0;
	char *p, line[MAXLEN];

	while ((len = getLine(line, MAXLEN)) > 0) {
		if ((p = alloc(len)) == NULL || nlines >= MAXLINES)
			return -1;
		line[len - 1] = '\0'; /* Remove newline character */
		strCpy(p, line);
		lineptr[nlines++] = p;
	}
	return nlines;
}

/** MAIN PROGRAM */
/*
 * main		: Parses command-line arguments, reads input lines, and prints the last n lines.
 * Input	: Command-line arguments for specifying the number of lines
 */
int main(int argc, char **argv) {
	int n = 10; /* Default number of lines */
	int nlines;

	/* Parse command-line arguments */
	if (argc > 2) {
		printf("Usage: tail [-n] where n is a positive number\n");
		return 1;
	} else if (argc == 2) {
		if (argv[1][0] == '-') {
			n = atoi(argv[1] + 1);
			if (n <= 0) {
				printf("Error: n must be a positive integer.\n");
				return 1;
			}
		} else {
			printf("Usage: tail [-n] where n is a positive number\n");
			return 1;
		}
	}

	/* Read input lines */
	nlines = readLines(lineptr);
	if (nlines < 0) {
		printf("Error: Too many input lines or memory allocation failed.\n");
		return 1;
	}

	/* Print the last n lines */
	printf("\nPrinting last %d lines:\n", (n > nlines) ? nlines : n);
	for (int i = (nlines > n ? nlines - n : 0); i < nlines; i++) {
		printf("%s\n", lineptr[i]);
	}

	return 0;
} /* End main() */
