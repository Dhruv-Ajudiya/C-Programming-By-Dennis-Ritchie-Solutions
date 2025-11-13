#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#define NULL 0
#define EOF (-1)
#define OPEN_MAX 20
#define PERMS 0666
#define BUFSIZE 1024

// FILE structure definition with fields instead of bit operations
typedef struct _iobuf {
	int cnt;        // characters left
	char *ptr;      // next character position
	char *base;     // location of buffer
	int read;       // file open for reading
	int write;      // file open for writing
	int unbuf;      // file is unbuffered
	int eof;        // EOF has occurred on this file
	int err;        // error occurred on this file
	int fd;         // file descriptor
} FILE;


extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

// Function prototypes
FILE *fopen(char *name, char *mode);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

// Macros for file operations
#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) write(p->fd, &x, 1)

#define getchar() getc(stdin)
#define putchar(x) putc(x, stdout)

#endif /* __SYSCALLS_H__ */
