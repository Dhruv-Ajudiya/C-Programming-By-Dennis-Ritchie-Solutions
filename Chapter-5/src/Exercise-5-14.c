/*
 * A program that sorts input lines based on specified options.
 * Supports options for numeric sort (-n) and reverse order (-r).
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** REQUIRED MACROS */
#define NUMERIC   1  /* Numeric sort */
#define DECR      2  /* Sort in decreasing order */
#define LINES     100 /* Maximum number of lines to be sorted */
#define ALLOCSIZE 1000 /* Size of available space */

/** FUNCTION PROTOTYPES */
int numCmp(char *s1, char *s2);
int readLines(char *lineptr[], int maxlines);
void writeLines(char *lineptr[], int nlines, int decr);
void qSort(void *v[], int left, int right, int (*comp)(void *, void *));
char *alloc(int n);
int getLine(char s[], int lim);

/** GLOBAL VARIABLES */
static char option = 0; /* Stores selected sort options */
static char allocbuf[ALLOCSIZE]; /* Storage for alloc */
static char *allocp = allocbuf; /* Next free position */

/** MAIN PROGRAM */
/*
 * main		: Parses command-line arguments, reads input lines, and sorts them based on specified options.
 * Input 	: Command-line arguments specifying sort options
 * Output	: Sorted lines printed to standard output
 */
int main(int argc, char *argv[]) {
	char *lineptr[LINES];
	int nlines; /* Number of input lines read */
	int c, rc = 0; /* Return code */

	/* Parse command-line arguments */
	while (--argc > 0 && (*++argv)[0] == '-') {
		while ((c = *++argv[0])) {
			switch (c) {
				case 'n': /* Numeric sort */
					option |= NUMERIC;
					break;
				case 'r': /* Reverse order */
					option |= DECR;
					break;
				default:
					printf("sort: illegal option %c\n", c);
					argc = 1;
					rc = -1;
					break;
			}
		}
	}

	if (argc) {
		printf("Usage: sort -nr\n");
	} else if ((nlines = readLines(lineptr, LINES)) > 0) {
		if (option & NUMERIC) {
			qSort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))numCmp);
		} else {
			qSort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))strcmp);
		}
		writeLines(lineptr, nlines, option & DECR);
	} else {
		printf("input too big to sort\n");
		rc = -1;
	}

	return rc;
} /* End main() */

/*
 * writeLines	: Writes sorted lines to standard output.
 * Input	: lineptr (array of pointers to lines), nlines (number of lines), decr (reverse order flag)
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void writeLines(char *lineptr[], int nlines, int decr) {
	if (decr) { /* Print in decreasing order */
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
 * numCmp	: Compares two strings numerically.
 * Input	: s1 (first string), s2 (second string)
 * Output	: -1 if s1 < s2, 1 if s1 > s2, 0 if equal
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int numCmp(char *s1, char *s2) {
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
 * readLines	: Reads input lines and stores them in lineptr.
 * Input	: lineptr (array of pointers to store lines), maxlines (maximum lines to read)
 * Output	: Number of lines read, or -1 on error
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int readLines(char *lineptr[], int maxlines) {
	int len, nlines = 0;
	char *p, line[1000];

	while ((len = getLine(line, 1000)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len - 1] = '\0'; /* Remove newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
} /* End readLines() */

/*
 * qSort	: Sorts an array using quicksort algorithm.
 * Input	: v (array of elements), left (start index), right (end index), comp (comparison function)
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void qSort(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right) {
		return;
	}

	swap(v, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qSort(v, left, last - 1, comp);
	qSort(v, last + 1, right, comp);
} /* End qSort() */

/*
 * swap		: Swaps two elements in an array.
 * Input	: v (array), i (index of first element), j (index of second element)
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void swap(void *v[], int i, int j) {
	void *temp = v[i];
	v[i] = v[j];
	v[j] = temp;
} /* End swap() */

/*
 * getLine	: Reads a line into s and returns its length.
 * Input	: s (array to store the line), lim (maximum line length)
 * Output	: Length of the line read
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getLine(char s[], int lim) {
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
 * alloc	: Allocates memory of size n.
 * Input	: n (size to allocate)
 * Output	: Pointer to allocated memory, or NULL on failure
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
} /* End alloc() */

/*
 * afree	: Frees memory allocated by alloc.
 * Input	: p (pointer to memory to free)
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void afree(char *p) {
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
		allocp = p;
	}
} /* End afree() */
