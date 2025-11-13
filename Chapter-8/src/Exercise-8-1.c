/*
 * A simplified version of the 'cat' command using low-level I/O system calls.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */

/** REQUIRED HEARDER FILES */
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** MACRO DEFINITIONS */
#define STDIN	0	/* File descriptor for standard input */
#define STDOUT	1	/* File descriptor for standard output */
#define STDERR	2	/* File descriptor for standard error */

/** FUNCTION PROTOTYPES */
void printError(const char *format, ...);
void copyFileContent(int inputFd, int outputFd);

/** MAIN PROGRAM */
/*
 * main		: Copies contents of provided files to standard output.
 * Input	: argc (Number of command-line arguments)
 *		  argv (Array of command-line arguments)
 * Return	: 0 if execution is successful, exits with error if a failure occurs
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
int main(int argc, char *argv[])
{
	int iFileDescriptor;	/* File descriptor for each file passed as argument */

	/* No arguments, copy from standard input to standard output */
	if (argc == 1) {
		copyFileContent(STDIN, STDOUT);
	} else {
		/* Iterate over each file provided as argument */
		while (--argc > 0) {
			if ((iFileDescriptor = open(*++argv, O_RDONLY)) == -1) {
				printError("cat: Cannot open file %s", *argv);
			} else {
				copyFileContent(iFileDescriptor, STDOUT);
				close(iFileDescriptor);
			}
		}
	}

	return 0;
} /* End main() */

/*
 * printError	: Prints an error message to standard error and exits the program
 * Input	: format (Format string for the error message)
 *		  ... (Variable arguments corresponding to the format specifiers)
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
void printError(const char *format, ...)
{
	va_list argList;		/* List to hold variable arguments */
	va_start(argList, format);	/* Initialize the argument list */

	/* Print error prefix and formatted message */
	fprintf(stderr, "error: ");
	vfprintf(stderr, format, argList);
	fprintf(stderr, "\n");

	va_end(argList);  /* Clean up the argument list */
	exit(1);
} /* End printError() */

/*
 * copyFileContent	: Copies data from input file descriptor to output file descriptor.
 * Input		: inputFd  (Input file descriptor)
 *			  outputFd (Output file descriptor)
 * Author		: Dhruv Ajudiya
 * Created		: 28 November 2024
 * Modified		: 28 November 2024
 */
void copyFileContent(int inputFd, int outputFd)
{
	int iBytesRead;            /* Number of bytes read in each iteration */
	char cBuffer[BUFSIZ];      /* Buffer to store data being copied */

	/* Read from input and write to output in chunks of BUFSIZ bytes */
	while ((iBytesRead = read(inputFd, cBuffer, BUFSIZ)) > 0) {
		if (write(outputFd, cBuffer, iBytesRead) != iBytesRead) {
			printError("cat: Write error occurred");
		}
	}
} /* End copyFileContent() */
