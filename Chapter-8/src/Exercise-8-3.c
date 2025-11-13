/*
 * A simplified implementation of basic file I/O operations in C.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */

/** REQUIRED HEADER FILES */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef NULL
#undef NULL
#endif

/** MACRO DEFINITIONS */
#define NULL		0
#define EOF		(-1)
#define BUFSIZ		1024
#define OPEN_MAX	20	/* Max #files open at once */
#define PERMS		0666	/* RW for owner, group, other */

/** ENUMERATION FOR FILE FLAGS */
enum _flags {
	_READ = 01,  /* File open for reading */
	_WRITE = 02, /* File open for writing */
	_UNBUF = 04, /* File is unbuffered */
	_EOF = 010,  /* EOF has occurred in this file */
	_ERR = 020   /* Error occurred in this file */
};

/** STRUCTURE DEFINITIONS */
typedef struct _iofbuf {
	int cnt;       /* Characters left */
	char *ptr;     /* Next character position */
	char *base;    /* Location of buffer */
	int flag;      /* Mode of file access */
	int fd;        /* File descriptor */
} FILE;

/** EXTERNAL VARIABLES */
FILE _iob[OPEN_MAX] = {
	{0, NULL, NULL, _READ, 0},
	{0, NULL, NULL, _WRITE, 1},
	{0, NULL, NULL, _WRITE | _UNBUF, 2}
};

/** FUNCTION PROTOTYPES */
FILE *fopen(char *name, char *mode);
int _fillbuf(FILE *fp);
int _flushbuf(int c, FILE *fp);
int fclose(FILE *fp);
int fflush(FILE *fp);

/** MACRO FUNCTIONS */
#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)
#define getc(p)     (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)   (--(p)->cnt >= 0 ?  *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)

/*
 * fopen	: Opens a file and returns a FILE pointer.
 * Input	: name (Name of the file to open)
 *		  mode (Mode in which to open the file: 'r', 'w', 'a')
 * Return	: Pointer to FILE structure or NULL on failure.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
FILE *fopen(char *name, char *mode) {
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
		return NULL;
	}

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
		if ((fp->flag & (_READ | _WRITE)) == 0) {
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
		return NULL; /* Couldn't access name */
	}

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;

	return fp;
} /* End fopen() */

/*
 * _fillbuf	: Allocates and fills input buffer.
 * Input	: fp (Pointer to FILE structure)
 * Return	: Next character or EOF on error.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
int _fillbuf(FILE *fp) {
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
		return EOF;
	}

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	if (fp->base == NULL) { /* No buffer yet */
		if ((fp->base = (char *)malloc(bufsize)) == NULL) {
			return EOF; /* Can't get buffer */
		}
	}

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	if (--fp->cnt < 0) {
		if (fp->cnt == -1) {
			fp->flag |= _EOF;
		} else {
			fp->flag |= _ERR;
		}
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char)*fp->ptr++;
} /* End _fillbuf() */

/*
 * _flushbuf	: Allocates and flushes output buffer.
 * Input	: c (Character to flush)
 *		  fp (Pointer to FILE structure)
 * Return	: Character flushed or EOF on error.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
int _flushbuf(int c, FILE *fp) {
	int bufsize;

	if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
		return EOF;
	}

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	if (fp->base == NULL) { /* No buffer yet */
		if ((fp->base = (char *)malloc(bufsize)) == NULL) {
			return EOF; /* Can't get buffer */
		}
	} else {
		unsigned nchar = fp->ptr - fp->base;
		if (write(fp->fd, fp->base, nchar) != nchar) {
			fp->flag |= _ERR;
			return EOF;
		}
	}

	fp->ptr = fp->base;
	*fp->ptr++ = (char)c;
	fp->cnt = bufsize - 1;
	return c;
} /* End _flushbuf() */

/*
 * fclose	: Closes a file.
 * Input	: fp (Pointer to FILE structure)
 * Return	: 0 on success, EOF on failure.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
int fclose(FILE *fp) {
	if (fflush(fp) == EOF) {
		return EOF;
	}
	free(fp->base);
	fp->base = fp->ptr = NULL;
	fp->cnt = 0;
	close(fp->fd);
	return 0;
} /* End fclose() */

/*
 * fflush	: Flushes file buffer.
 * Input	: fp (Pointer to FILE structure)
 * Return	: 0 on success, EOF on failure.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
int fflush(FILE *fp) {
	if ((fp->flag & _WRITE) != _WRITE) {
		fp->flag |= _ERR;
		write(2, "Error at fflush\n", 17);
		return EOF;
	}
	if (_flushbuf(0, fp) == EOF) {
		write(2, "Error at fflush\n", 17);
		return EOF;
	}
	fp->ptr = fp->base;
	fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	return 0;
} /* End fflush() */

/** MAIN PROGRAM */
/*
 * main : Demonstrates basic file operations by copying contents
 *        of one file to another.
 */
int main(int argc, char *argv[]) {
	FILE *fpin, *fpout;
	char c;

	if ((fpin = fopen("syscalls.h", "r")) == NULL) {
		return 1;
	}

	if ((fpout = fopen("temp.txt", "w")) == NULL) {
		return 1;
	}

	while ((c = getc(fpin)) != EOF) {
		putc(c, fpout);
	}

	fclose(fpout);
	return 0;
}
