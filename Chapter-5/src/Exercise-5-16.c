/*
 * This program sorts input lines based on various criteria like numeric order,
 * reverse order, case insensitivity, and directory order.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** REQUIRED MACROS */
#define MAXLINES    5000  /* Maximum number of lines to be sorted */
#define ALLOCSIZE   10000 /* Available space for input lines */
#define MAXLEN      1000  /* Maximum length of a single input line */

/** GLOBAL VARIABLES */
char *lineptr[MAXLINES]; /* Pointers to text lines */
int numeric = 0;         /* 1 if numeric sort */
int reverse = 0;         /* 1 if reverse order */
int fold = 0;            /* 1 if case insensitive */
int dire = 0;            /* 1 if directory order */

/** FUNCTION PROTOTYPES */
int readLines(char *lineptr[], char *buff, int nlines);
void writeLines(char *lineptr[], int nlines, int reverse);
void qSort(void **v, int left, int right, int (*comp)(void *, void *));
int numCmp(char *s1, char *s2);
int strCmp(char *s1, char *s2);
int getLine(char s[], int lim);

/** MAIN PROGRAM */
/*
 * main: Reads input lines, sorts them based on command-line options,
 *       and prints the sorted output.
 */
int main(int argc, char *argv[])
{
	char buff[ALLOCSIZE];
	int nlines; /* Number of input lines read */
	int c;

	/* Parse command-line options */
	while (--argc > 0 && (*++argv)[0] == '-') {
		while ((c = *++argv[0])) {
			switch (c) {
				case 'n':
					numeric = 1;
					break;
				case 'r':
					reverse = 1;
					break;
				case 'f':
					fold = 1;
					break;
				case 'd':
					dire = 1;
					break;
				default:
					printf("Invalid command: %c\n", c);
					return 1;
			}
		}
	}

	/* Read lines and sort them */
	if ((nlines = readLines(lineptr, buff, MAXLINES)) >= 0) {
		qSort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numCmp : strCmp));
		writeLines(lineptr, nlines, reverse);
		return 0;
	} else {
		printf("Input too large to sort\n");
		return 1;
	}
} /* End main() */

/*
 * readLines	: Reads input lines into the buffer and sets up line pointers.
 * Input	: lineptr (array of line pointers), buff (buffer for lines), maxlines (maximum lines).
 * Return	: Number of lines read, or -1 if input exceeds buffer size.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int readLines(char *lineptr[], char *buff, int maxlines)
{
	int nlines = 0, len;
	char *p = buff, line[MAXLEN];

	while ((len = getLine(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (ALLOCSIZE - (p - buff)) < len) {
			return -1;
		} else {
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
			*(p - 1) = '\0';
		}
	}
	return nlines;
} /* End readLines() */

/*
 * writeLines	: Writes sorted lines to standard output.
 * Input	: lineptr (array of line pointers), nlines (number of lines), reverse (if reverse order).
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void writeLines(char *lineptr[], int nlines, int reverse)
{
	if (reverse) {
		for (int i = nlines - 1; i >= 0; i--) {
			printf("%s\n", lineptr[i]);
		}
	} else {
		for (int i = 0; i < nlines; i++) {
			printf("%s\n", lineptr[i]);
		}
	}
} /* End writeLines() */

/*
 * getLine	: Reads a line from input.
 * Input	: s (string buffer), lim (maximum length).
 * Return	: Length of the line read.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getLine(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
} /* End getLine() */

/*
 * swap		: Swaps two elements in an array.
 * Input	: v (array), i, j (indices to swap).
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void swap(void *v[], int i, int j)
{
	void *temp = v[i];
	v[i] = v[j];
	v[j] = temp;
} /* End swap() */

/*
 * qSort	: Sorts an array using quicksort.
 * Input	: v (array), left, right (indices), comp (comparison function).
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void qSort(void *v[], int left, int right, int (*comp)(void *, void *))
{
	if (left >= right) {
		return;
	}

	swap(v, left, (left + right) / 2);
	int last = left;
	for (int i = left + 1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qSort(v, left, last - 1, comp);
	qSort(v, last + 1, right, comp);
} /* End qSort() */

/*
 * numCmp	: Compares two strings numerically.
 * Input	: s1, s2 (strings).
 * Return	: -1 if s1 < s2, 1 if s1 > s2, 0 if equal.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int numCmp(char *s1, char *s2)
{
	double v1 = atof(s1);
	double v2 = atof(s2);

	if (v1 < v2) {
		return -1;
	} else if (v1 > v2) {
		return 1;
	} else {
		return 0;
	}
} /* End numCmp() */

/*
 * strCmp	: Compares two strings, optionally ignoring case and non-alphanumeric characters.
 * Input	: s1, s2 (strings).
 * Return	: -1 if s1 < s2, 1 if s1 > s2, 0 if equal.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int strCmp(char *s1, char *s2)
{
	char a, b;

	do {
		if (dire) {
			while (!isalnum(*s1) && *s1 != '\0' && *s1 != ' ') {
				s1++;
			}
			while (!isalnum(*s2) && *s2 != '\0' && *s2 != ' ') {
				s2++;
			}
		}

		a = fold ? tolower(*s1++) : *s1++;
		b = fold ? tolower(*s2++) : *s2++;

		if (a == b && a == '\0') {
			return 0;
		}
	} while (a == b);

	return a - b;
} /* End strCmp() */
