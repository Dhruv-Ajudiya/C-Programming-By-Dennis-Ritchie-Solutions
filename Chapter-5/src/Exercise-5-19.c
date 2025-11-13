/*
 * This program converts C declarations into words and vice versa.
 * It ensures no redundant parentheses are added to declarations.
 * Author	: Dhruv Ajudiya 
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/** REQUIRED MACROS */
#define MAXTOKEN    100   /* Maximum length of a token */
#define BUFSIZE     100   /* Buffer size for ungetch */

/** ENUMERATIONS DEFINITION */
enum {
	NAME,       /* Token type: name (identifier) */
	PARENS,     /* Token type: parentheses () */
	BRACKETS    /* Token type: brackets [] */
};

enum {
	NO,         /* Boolean flag: No */
	YES         /* Boolean flag: Yes */
};

/** GLOBAL VARIABLES */
int tokentype;         /* Type of last token */
char token[MAXTOKEN];  /* Last token string */
char out[1000];        /* Output string */

int prevtoken = NO;    /* Flag to check if there is a previous token */

char buf[BUFSIZE];     /* Buffer for ungetch */
int bufp = 0;          /* Buffer pointer */

/** FUNCTION PROTOTYPES */
int getch(void);
void ungetch(int c);
int getToken(void);
int nextToken(void);

/** MAIN PROGRAM */
/*
 * main : Parses C declarations and converts them into valid syntax.
 *	  Ensures no redundant parentheses are added to declarations.
 */
int main(void)
{
	int type;               /* Stores the current token type */
	char temp[MAXTOKEN];    /* Temporary buffer for constructing output */

	while (getToken() != EOF) {
		strncpy(out, token, sizeof(out) - 1); /* Initialize output with the first token */
		out[sizeof(out) - 1] = '\0';          /* Ensure null-termination */

		while ((type = getToken()) != '\n') {
			if (type == PARENS || type == BRACKETS) {
				strncat(out, token, sizeof(out) - strlen(out) - 1); /* Append parentheses or brackets */
			} else if (type == '*') {
				/* Handle pointers with precedence rules */
				if ((type = nextToken()) == PARENS || type == BRACKETS) {
					snprintf(temp, sizeof(temp) - 1, "(*%.90s)", out);
				} else {
					snprintf(temp, sizeof(temp) - 1, "*%.90s", out);
				}
				temp[sizeof(temp) - 1] = '\0'; /* Ensure null-termination */
				strncpy(out, temp, sizeof(out) - 1);
				out[sizeof(out) - 1] = '\0';
			} else if (type == NAME) {
				snprintf(temp, sizeof(temp) - 1, " %.45s %.45s", token, out); /* Split token and out */
				temp[sizeof(temp) - 1] = '\0'; /* Ensure null-termination */
				strncpy(out, temp, sizeof(out) - 1);
				out[sizeof(out) - 1] = '\0';
			} else {
				printf("invalid input at %s\n", token); /* Handle invalid tokens */
			}
		}
		printf("%s\n", out); /* Print the parsed declaration */
	}
	return 0;
} /* End main() */

/*
 * getch	: Fetches a character from the input buffer or stdin
 * Return	: Character from buffer or input
 * Author	: Dhruv Ajudiya 
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
} /* End getch() */

/*
 * ungetch	: Pushes a character back onto the input buffer
 * Input	: c (Character to push back onto the buffer)
 * Author	: Dhruv Ajudiya 
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void ungetch(int c)
{
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	} else {
		buf[bufp++] = c;
	}
} /* End ungetch() */

/*
 * getToken	: Extracts the next token from input
 * Return	: Token type (NAME, PARENS, BRACKETS, etc.)
 * Author	: Dhruv Ajudiya 
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getToken(void)
{
	int c;
	char *p = token;

	if (prevtoken == YES) {
		prevtoken = NO;
		return tokentype;
	}

	while ((c = getch()) == ' ' || c == '\t')
		; /* Skip spaces and tabs */

	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
} /* End getToken() */

/*
 * nextToken	: Retrieves the next token and pushes it back onto the stream
 * Return	: Token type
 * Author	: Dhruv Ajudiya 
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int nextToken(void)
{
	int type = getToken();
	prevtoken = YES;
	return type;
} /* End nextToken() */
