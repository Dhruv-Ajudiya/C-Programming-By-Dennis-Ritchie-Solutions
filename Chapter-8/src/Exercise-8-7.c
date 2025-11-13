/*
 * Custom memory allocation and deallocation routines with improved error checking.
 * Author	: Dhruv Ajudiya
 * Created	: 7 November 2024
 * Modified	: 28 November 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** MACRO DEFINITIONS */
#define MAXBYTES (unsigned)10240 /* Maximum allocation size */
#define NALLOC 1024              /* Minimum units to request */

/** TYPE DEFINITIONS */
typedef long Align; /* Alignment type */

union header {
	struct {
		union header *ptr; /* Next block if on free list */
		unsigned size;     /* Size of this block */
	} s;
};

typedef union header Header;

/** STATIC VARIABLES */
static unsigned maxalloc = 0;    /* Maximum units allocated */
static Header base;              /* Empty list to get started */
static Header *freep = NULL;     /* Start of free list */

/** FUNCTION PROTOTYPES */
static Header *morecore(unsigned);
void *mymalloc(unsigned);
void myfree(void *);

/*
 * morecore	: Requests more memory from the system.
 * Input	: nu (Number of units to allocate)
 * Return	: Pointer to the newly allocated memory, or NULL if allocation fails.
 * Author	: Dhruv Ajudiya
 * Created	: 7 November 2024
 * Modified	: 28 November 2024
 */
static Header *morecore(unsigned nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC) {
		nu = NALLOC;
	}

	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *)-1) { /* No space available */
		return NULL;
	}

	up = (Header *)cp;
	up->s.size = nu;
	myfree((void *)(up + 1));
	return freep;
} /* End morecore() */

/*
 * mymalloc	: Allocates memory of the requested size.
 * Input	: nbytes (Number of bytes to allocate)
 * Return	: Pointer to the allocated memory, or NULL if allocation fails.
 * Author	: Dhruv Ajudiya
 * Created	: 7 November 2024
 * Modified	: 28 November 2024
 */
void *mymalloc(unsigned nbytes)
{
	Header *p, *prevp;
	unsigned nunits;

	if (nbytes > MAXBYTES) {
		fprintf(stderr, "alloc: can't allocate more than %u bytes\n", MAXBYTES);
		return NULL;
	}

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits) {
				prevp->s.ptr = p->s.ptr;
			} else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p + 1);
		}

		if (p == freep) { /* Wrapped around free list */
			if ((p = morecore(nunits)) == NULL) {
				return NULL;
			}
		}
	}
} /* End mymalloc() */

/*
 * myfree	: Frees a previously allocated block of memory.
 * Input	: ap (Pointer to the block to be freed)
 * Author	: Dhruv Ajudiya
 * Created	: 7 November 2024
 * Modified	: 28 November 2024
 */
void myfree(void *ap)
{
	Header *bp, *p;

	if (ap == NULL) {
		return; /* Do nothing if NULL pointer */
	}

	bp = (Header *)ap - 1; /* Point to block header */

	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
			break; /* Freed block at start or end of arena */
		}
	}

	if (bp + bp->s.size == p->s.ptr) { /* Join to upper neighbor */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else {
		bp->s.ptr = p->s.ptr;
	}

	if (p + p->s.size == bp) { /* Join to lower neighbor */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else {
		p->s.ptr = bp;
	}

	freep = p;
} /* End myfree() */

/*
 * main : Demonstrates usage of mymalloc and myfree.
 */
int main(int argc, char *argv[])
{
	int *p = NULL;
	int i;

	p = mymalloc(1000);
	if (p == NULL) {
		printf("mymalloc returned NULL\n");
	} else {
		for (i = 0; i <= 100; i++) {
			printf("%08X ", p[i]);
			if (i % 8 == 7) {
				printf("\n");
			}
		}
		printf("\n");
		myfree(p);
	}

	return 0;
} /* End main() */
