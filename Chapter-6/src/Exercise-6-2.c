/*
 * This program reads a C program and prints in alphabetical order each group
 * of variable names that are identical in the first N characters but differ thereafter.
 * Handles comments, string constants, and preprocessor directives by skipping over them.
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */

/** REQUIRED HEADER FILES */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** MACRO DEFINITIONS */
#define DEFAULT_PREFIX_LEN 6   /* Default prefix length */
#define MAX_WORD_LENGTH    100 /* Maximum length of a word */
#define BUFFER_SIZE        100 /* Size of buffer for pushed back input */

/** STRUCTURE DEFINITIONS */
struct treeNode {
	char *word;
	int count;
	struct treeNode *left;
	struct treeNode *right;
};

/** GLOBAL VARIABLES */
char inputBuffer[BUFFER_SIZE]; /* Buffer to store input pushed back into input */
int bufferPosition = 0;       /* Next free position in input buffer */

/** FUNCTION PROTOTYPES */
struct treeNode *addTreeNode(struct treeNode *root, char *word);
struct treeNode *allocateTreeNode(void);
char *duplicateString(char *source);
void printTree(struct treeNode *root);
void freeTree(struct treeNode *root);
int getWord(char *word, int maxLength);
int getCharacter(void);
void ungetCharacter(int character);

/** MAIN PROGRAM */
/*
 * main: Reads input from a C program, extracts variable names, and prints
 *       them in alphabetical order grouped by a prefix length.
 */
int main(int argc, char *argv[])
{
	struct treeNode *root = NULL; /* Root of the binary search tree */
	char word[MAX_WORD_LENGTH];  /* Buffer to store the current word */
	int prefixLength = DEFAULT_PREFIX_LEN;

	/* Parse command-line arguments */
	if (argc == 2) {
		prefixLength = atoi(argv[1]);
		if (prefixLength <= 0) {
			printf("Error: Invalid prefix length. Using default value %d.\n", DEFAULT_PREFIX_LEN);
			prefixLength = DEFAULT_PREFIX_LEN;
		}
	} else if (argc > 2) {
		printf("Error: Too many arguments. Usage: program [prefix_length]\n");
		return 1;
	}

	/* Process input */
	while (getWord(word, MAX_WORD_LENGTH) != EOF) {
		if ((isalpha(word[0]) || word[0] == '_') && strlen(word) >= prefixLength) {
			root = addTreeNode(root, word);
		}
	}

	/* Print results */
	printf("Variable names grouped alphabetically by prefix:\n");
	printTree(root);

	/* Clean up */
	freeTree(root);
	return 0;
} /* End main() */

/*
 * addTreeNode	: Adds a word to the binary search tree rooted at `root`.
 * Input	: root (pointer to the root of the tree)
 *		  word (word to add to the tree)
 * Return	: Pointer to the updated tree root
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */
struct treeNode *addTreeNode(struct treeNode *root, char *word)
{
	int comparison;

	if (root == NULL) {
		root = allocateTreeNode();
		root->word = duplicateString(word);
		root->count = 1;
		root->left = root->right = NULL;
	} else if ((comparison = strcmp(word, root->word)) == 0) {
		root->count++;
	} else if (comparison < 0) {
		root->left = addTreeNode(root->left, word);
	} else {
		root->right = addTreeNode(root->right, word);
	}
	return root;
} /* End addTreeNode() */

/*
 * allocateTreeNode	: Allocates memory for a new tree node.
 * Return		: Pointer to the newly allocated tree node
 * Author		: Dhruv Ajudiya
 * Created		: 27 November 2024
 * Modified		: 27 November 2024
 */
struct treeNode *allocateTreeNode(void)
{
	return (struct treeNode *)malloc(sizeof(struct treeNode));
} /* End allocateTreeNode() */

/*
 * duplicateString	: Creates a duplicate of the input string.
 * Input		: source (input string to duplicate)
 * Return		: Pointer to the duplicated string
 * Author		: Dhruv Ajudiya
 * Created		: 27 November 2024
 * Modified		: 27 November 2024
 */
char *duplicateString(char *source)
{
	char *copy = (char *)malloc(strlen(source) + 1);
	if (copy != NULL) {
		strcpy(copy, source);
	}
	return copy;
} /* End duplicateString() */

/*
 * printTree	: Prints the binary search tree in-order.
 * Input	: root (pointer to the root of the tree)
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */
void printTree(struct treeNode *root)
{
	if (root != NULL) {
		printTree(root->left);
		printf("%s\n", root->word);
		printTree(root->right);
	}
} /* End printTree() */

/*
 * freeTree	: Frees all memory associated with the binary search tree.
 * Input	: root (pointer to the root of the tree)
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */
void freeTree(struct treeNode *root)
{
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root->word);
		free(root);
	}
} /* End freeTree() */

/*
 * getWord	: Reads the next word or token from input.
 * Input	: word (buffer to store the word)
 *		  maxLength (maximum length of the word)
 * Return	: First character of the word or EOF if end of input
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */
int getWord(char *word, int maxLength)
{
	int currentChar;
	char *bufferPtr = word;

	/* Skip whitespace */
	while (isspace(currentChar = getCharacter()))
		;

	if (currentChar != EOF) {
		*bufferPtr++ = currentChar;
	}

	/* Handle non-alphabetic tokens */
	if (!isalpha(currentChar) && currentChar != '_') {
		*bufferPtr = '\0';
		return currentChar;
	}

	/* Read alphanumeric characters */
	for (; --maxLength > 0; bufferPtr++) {
		if (!isalnum(*bufferPtr = getCharacter()) && *bufferPtr != '_') {
			ungetCharacter(*bufferPtr);
			break;
		}
	}
	*bufferPtr = '\0';

	return word[0];
} /* End getWord() */

/*
 * getCharacter	: Gets a (possibly pushed-back) character from input.
 * Return	: The character read from input
 * Author	: Dhruv Ajudiya
 * Created	: 27 November 2024
 * Modified	: 27 November 2024
 */
int getCharacter(void)
{
	return (bufferPosition > 0) ? inputBuffer[--bufferPosition] : getchar();
} /* End getCharacter() */

/*
 * ungetCharacter	: Pushes a character back into the input buffer.
 * Input		: character (the character to push back)
 * Author		: Dhruv Ajudiya
 * Created		: 27 November 2024
 * Modified		: 27 November 2024
 */
void ungetCharacter(int character)
{
	if (bufferPosition >= BUFFER_SIZE) {
		printf("Error: Input buffer overflow\n");
	} else {
		inputBuffer[bufferPosition++] = character;
	}
} /* End ungetCharacter() */
