/*
 * Custom calloc Implementation
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>

/** FUNCTION PROTOTYPES */
void *myCalloc(unsigned int n, unsigned int size);

/** MAIN PROGRAM */
/*
 * main		: Demonstrates custom calloc implementation.
 * Input	: argc (Number of command-line arguments)
 *		  argv (Array of command-line arguments)
 */
int main(int argc, char *argv[])
{
	int *p = NULL; /* Pointer to allocated memory */
	int i = 0;     /* Loop index */

	/* Allocate memory using custom calloc */
	p = myCalloc(100, sizeof *p);
	if (NULL == p) {
		printf("myCalloc returned NULL\n");
	} else {
		/* Initialize and print allocated memory */
		for (i = 0; i < 100; i++) {
			printf("%08X", p[i]);
			if (i % 8 == 7) {
				printf("\n");
			}
		}
		printf("\n");
		free(p); /* Free allocated memory */
	}

	return 0;
} /* End main() */

/*
 * myCalloc	: Allocates memory for an array and initializes it to zero.
 * Input	: n (Number of elements to allocate)
 *		  size (Size of each element in bytes)
 * Return	: Pointer to allocated memory, or NULL on failure
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
void *myCalloc(unsigned int n, unsigned int size)
{
	unsigned int i, nb; /* Total bytes to allocate */
	char *p, *q;        /* Pointers to allocated memory */

	nb = n * size;

	/* Allocate memory */
	if ((p = q = malloc(nb)) != NULL) {
		/* Initialize memory to zero */
		for (i = 0; i < nb; i++) {
			*p++ = 0;
		}
	}
	return q;
} /* End myCalloc() */
