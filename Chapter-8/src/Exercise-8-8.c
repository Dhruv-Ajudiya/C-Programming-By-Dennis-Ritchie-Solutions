/*
 * This program modifies the free memory management implementation of malloc() and free()
 * It introduces two primary functions, bfree() and wtbfree(), to manage memory more flexibly
 * by adding blocks to the free list and handling smaller unaligned memory fragments separately.
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
 
/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** MACRO DEFINITIONS */
#define MAXBYTES (unsigned)1024
#define ALIGN(p) \
    (sizeof(Align) - ((uintptr_t)(p) % sizeof(Align))) % sizeof(Align)


/** TYPE DEFINITIONS */
typedef long Align;

union header {
	struct {
		union header *ptr; /* Next block if on the free list */
		unsigned size;     /* Size of this block */
	} s;
	Align x;
};

typedef union header Header;

/** STATIC VARIABLES */
static Header base;          /* Empty list to get started */
static Header *freep = NULL; /* Start of free list */
static struct wtbheader *headptr;

/** STRUCTURE DEFINITIONS */
struct wtbheader {
	struct wtbheader *next;
	void *p;
	unsigned n;
};

/** FUNCTION PROTOTYPES */
void wtbfree(void *p, unsigned n);
void bfree(void *p, unsigned n);
static void try_to_free(struct wtbheader *p);

/*
 * bfree	: Adds a block into the free list maintained by malloc and free.
 * Input	: p (Pointer to the block to be added)
 *		  n (Size of the block in bytes)
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
void bfree(void *p, unsigned n)
{
	unsigned align, s, r;

	if (n < sizeof(Header)) { /* Can't free less than this */
		wtbfree(p, n);
		return;
	}

	align = ALIGN(p);
	if (align) {           /* Adjust alignment */
		wtbfree(p, align); /* Add to the wtbfree list */
		p = (char *)p + align;
		n -= align;
	}
	s = n / sizeof(Header);
	r = n % sizeof(Header);

	if (r) { /* Add trailing bits to wtbfree */
		wtbfree((char *)p + n + r, r);
	}

	if (s) { /* If there is something left to free */
		if (freep == NULL) { /* Setup free list if empty */
			base.s.ptr = freep = &base;
			base.s.size = 0;
		}

		((Header *)p)->s.size = s;
		free((Header *)p + 1);
	}
} /* End bfree() */

/*
 * try_to_free	: Attempts to add a wtbheader block to the free list if possible.
 * Input	: p (Pointer to the wtbheader structure)
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
static void try_to_free(struct wtbheader *p)
{
	char *tp;
	unsigned align, n;

	tp = p->p;
	align = ALIGN(p->p);

	if ((align < p->n) && ((p->n - align) % sizeof(Header) == 0)) {
		tp += align;
		n = p->n - align;
		p->n = align;

		((Header *)tp)->s.size = n / sizeof(Header);
		free((Header *)tp + 1);
	}
} /* End try_to_free() */

/*
 * wtbfree	: Adds a fragment to the Waiting To Be free (wtbfree) list.
 * Input	: p (Pointer to the fragment)
 *		  n (Size of the fragment in bytes)
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
void wtbfree(void *p, unsigned n)
{
	struct wtbheader *hp, *prevp;

	if (headptr == NULL) { /* First use */
		if (!(headptr = malloc(sizeof *headptr))) /* Can't save fragment, dump it */
			return;
		headptr->p = p;
		headptr->n = n;
		headptr->next = NULL;
	} else if (p < headptr->p) { /* Special case: Less than head */
		if ((char *)p + n == headptr->p) { /* Merge */
			headptr->p = p;
			headptr->n = n;
			try_to_free(headptr);

			if (!headptr->n) { /* Delete empty node */
				void *tp = headptr;
				headptr = headptr->next;
				free(tp);
			}
		} else {
			struct wtbheader *tp;
			if (!(tp = malloc(sizeof *tp))) /* Can't save fragment, dump it */
				return;
			tp->p = p;
			tp->n = n;
			tp->next = headptr;
			headptr = tp;
		}
	} else {
		for (prevp = hp = headptr; hp->next && p > hp->next->p; prevp = hp, hp = hp->next) {
			; /* Just advance */
		}

		if ((char *)hp->p + hp->n == p) { /* Merge to current */
			hp->n += n;
			try_to_free(hp);

			if (!hp->n) {
				if (hp == headptr)
					headptr = NULL;
				prevp->next = hp->next;
				free(hp);
			}
		} else if (hp->next && (char *)p + n == hp->next->p) { /* Merge to next */
			hp->next->p = p;
			hp->next->n += n;
			try_to_free(hp->next);

			if (!hp->next->n) { /* Delete empty node */
				void *tp = hp->next;
				hp->next = hp->next->next;
				free(tp);
			}
		} else { /* Insert */
			struct wtbheader *tp;
			if (!(tp = malloc(sizeof *tp))) /* Can't save fragment, dump */
				return;
			tp->p = p;
			tp->n = n;

			tp->next = hp->next;
			hp->next = tp;
		}
	}
} /* End wtbfree() */

/*
 * main : Demonstrates the usage of bfree and wtbfree.
 */
int main(int argc, char *argv[])
{
	int *p = NULL;
	int i = 0;

	p = malloc(100 * sizeof *p);
	if (NULL == p) {
		printf("malloc returned NULL\n");
	} else {
		for (i = 0; i <= 100; i++) {
			printf("%08X", p[i]);
			if (i % 8 == 7) {
				printf("\n");
			}
		}
		printf("\n");
		bfree(p, 1 * sizeof *p);
	}
	return 0;
} /* End main() */
