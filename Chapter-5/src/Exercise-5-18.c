/*
 * This program converts declarations into words, ensuring recovery from input errors.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */

/** REQUIRED HEADER FILES */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** REQUIRED MACRO */
#define MAXTOKEN       100    /* Maximum token length */
#define BUFSIZE        100    /* Buffer size */

/** FUNCTION PROTOTYPES */
void dcl(void);              /* Parse a declaration */
void dirdcl(void);           /* Parse a direct declaration */
int gettoken(void);          /* Retrieve next token */
void recover(void);          /* Recover from input errors */
int getch(void);             /* Get next character */
void ungetch(int c);         /* Unget a character */

/** STRUCTURE DEFINITION */
struct keywords {
	char *name;              /* Keyword name */
} kw[] = {
	{"auto"}, {"break"}, {"case"}, {"char"},
	{"const"}, {"continue"}, {"default"}, {"do"},
	{"double"}, {"else"}, {"enum"}, {"extern"},
	{"float"}, {"for"}, {"goto"}, {"if"},
	{"int"}, {"long"}, {"register"}, {"return"},
	{"short"}, {"signed"}, {"sizeof"}, {"static"},
	{"struct"}, {"switch"}, {"typedef"}, {"union"},
	{"unsigned"}, {"void"}, {"volatile"}, {"while"}
};

/** GLOBAL VARIABLES */
enum { NAME, PARENS, BRACKETS }; /* Token types */
int tokentype;                  /* Last token type */
char token[MAXTOKEN];           /* Last token string */
char name[MAXTOKEN];            /* Identifier name */
char datatype[MAXTOKEN];        /* Data type (char, int, etc.) */
char out[1000];                 /* Output buffer */
int error = 0;                  /* Error flag */
char buf[BUFSIZE];              /* Buffer for ungetch */
int bufp = 0;                   /* Buffer pointer */

/** MAIN PROGRAM */
/*
 * main	: Reads input, parses declarations, and outputs results.
 */
int main()
{
	while (gettoken() != EOF) {
		strcpy(datatype, token); /* First token is the datatype */
		out[0] = '\0';
		dcl(); /* Parse the rest of the line */

		if (tokentype != '\n') {
			printf("syntax error\n");
			error = 1;
		}

		for (int i = 0; i < 32; i++) {
			if (strcmp(name, kw[i].name) == 0) {
				printf("Variable name is a keyword\n");
				error = 1;
			}
		}

		if (!error) {
			printf("%s: %s %s\n", name, out, datatype);
		}
		error = 0;
	}
	return 0;
} /* End main() */

/*
 * gettoken	: Retrieves the next token from the input.
 * Output	: Updates global variables tokentype and token.
 * Return	: Token type (NAME, PARENS, BRACKETS, or a character).
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;

	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
} /* End gettoken() */

/*
 * dcl		: Parses a declaration and constructs the output string.
 * Output	: Updates the global variable out with the parsed declaration.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void dcl(void)
{
	int ns;
	for (ns = 0; gettoken() == '*'; ) /* Count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
} /* End dcl() */

/*
 * dirdcl	: Parses a direct declaration.
 * Output	: Updates the global variable out with the parsed direct declaration.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void dirdcl(void)
{
	int type;

	if (tokentype == '(') { /* ( dcl ) */
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	} else if (tokentype == NAME) { /* Variable name */
		strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS) {
			strcat(out, " function returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
} /* End dirdcl() */

/*
 * recover	: Skips erroneous input until a new line or EOF is reached.
 * Output	: Discards erroneous input.
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
void recover(void)
{
	int c;
	while ((c = gettoken()) != '\n' && c != EOF) {
		/* Skip erroneous input */
	}
} /* End recover() */

/*
 * getch	: Retrieves the next character from input or buffer.
 * Output	: Character from input or buffer
 * Return	: Next character
 * Author	: Dhruv Ajudiya
 * Created	: 28 October 2024
 * Modified	: 28 October 2024
 */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
} /* End getch() */

/*
 * ungetch	: Pushes a character back to the buffer.
 * Input	: c (character to push back).
 * Output	: Updates the buffer.
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

