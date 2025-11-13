/*
 * This program reads from files or standard input and writes to standard output. 
 * It replicates the behavior of the `cat` command using custom file I/O functions.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */

/** REQUIRED HEADER FILES */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/** MACRO DEFINITIONS */
#define PERMS		0666	/* Default file permissions */
#define BUFSIZE		1024	/* Buffer size for file reading */
#define OPEN_MAX	20	/* Maximum number of open files */

/** TYPE DEFINITIONS */
typedef struct _MY_FILE {
	int cnt;	/* Characters left */
	char *ptr;	/* Next character position */
	char *base;	/* Location of the buffer */
	int read;	/* File open for reading */
	int write;	/* File open for writing */
	int unbuf;	/* Unbuffered if nonzero */
	int eof;	/* EOF has occurred */
	int err;	/* Error indicator */
	int fd;		/* File descriptor */
} MY_FILE;

/** GLOBAL VARIABLES */
MY_FILE _iob[OPEN_MAX] = {
	{ 0, (char *)0, (char *)0, 1, 0, 0, 0, 0, 0 },
	{ 0, (char *)0, (char *)0, 0, 1, 0, 0, 0, 1 },
	{ 0, (char *)0, (char *)0, 0, 1, 1, 0, 0, 2 }
};

/** FUNCTION PROTOTYPES */
MY_FILE *my_fopen(char *name, char *mode);
int _fillbuf(MY_FILE *fp);

/*
 * my_fopen	: Opens a file and returns a custom file pointer (MY_FILE).
 * Input	: name (name of the file), mode (mode of opening file: r, w, a)
 * Return	: Pointer to the MY_FILE structure or NULL on failure.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
MY_FILE *my_fopen(char *name, char *mode)
{
	int fd;
	MY_FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
		return NULL;
	}

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
		if (!fp->read && !fp->write) {
			break; /* Found free slot */
		}
	}

	if (fp >= _iob + OPEN_MAX) {
		return NULL; /* No free slots */
	}

	if (*mode == 'w') {
		fd = creat(name, PERMS);
	} else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1) {
			fd = creat(name, PERMS);
		}
		lseek(fd, 0L, 2);
	} else {
		fd = open(name, O_RDONLY, 0);
	}

	if (fd == -1) {
		return NULL; /* Couldn't open file */
	}

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->read = (*mode == 'r');
	fp->write = !fp->read;
	fp->unbuf = fp->eof = fp->err = 0;

	return fp;
} /* End my_fopen() */

/*
 * _fillbuf	: Allocates and fills the input buffer.
 * Input	: fp (pointer to MY_FILE structure)
 * Return	: Next character in the buffer, or EOF on failure.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
int _fillbuf(MY_FILE *fp)
{
	int bufsize;

	if (!fp->read || fp->eof || fp->err) {
		return EOF;
	}

	bufsize = fp->unbuf ? 1 : BUFSIZE;

	if (fp->base == NULL) {
		if ((fp->base = (char *)malloc(bufsize)) == NULL) {
			return EOF; /* No memory */
		}
	}

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	if (--fp->cnt < 0) {
		if (fp->cnt == -1) {
			fp->eof = 1;
		} else {
			fp->err = 1;
		}
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char)*fp->ptr++;
} /* End _fillbuf() */

/*
 * my_getc	: Gets the next character from the file.
 * Input	: fp (pointer to MY_FILE structure)
 * Return	: Next character or EOF on error.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
int my_getc(MY_FILE *fp)
{
	if (fp->cnt <= 0) {
		if (_fillbuf(fp) == EOF) {
			return EOF;
		}
	}
	fp->cnt--;
	return (unsigned char) *fp->ptr++;
}

/** MAIN PROGRAM */
/*
 * main : Reads from files or stdin and writes to stdout.
 */
int main(int argc, char *argv[])
{
	MY_FILE *fp;
	char c;

	if (argc == 1) {
		/* No files provided, read from stdin */
		while ((c = my_getc((MY_FILE *)stdin)) != EOF) {  // Cast stdin to MY_FILE*
			putchar(c);
		}
	} else {
		while (--argc > 0) {
			if ((fp = my_fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "Error: Cannot open file %s\n", *argv);
				return 1;
			} else {
				while ((c = my_getc(fp)) != EOF) {  // Use my_getc for file reading
					putchar(c);
				}
			}
		}
	}

	return 0;
} /* End main() */

