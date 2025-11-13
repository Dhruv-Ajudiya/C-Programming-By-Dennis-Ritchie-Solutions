/*
 * File Size and Attributes Display Utility
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/** MACRO DEFINITIONS */
#define MAX_PATH 1024

/** FUNCTION PROTOTYPES */
void fsize(const char *name);
void dirwalk(const char *dir, void (*fcn)(const char *));

/** MAIN PROGRAM */
/*
 * main : It determines whether to calculate the sizes and attributes of files in the current
 *	  directory or those specified by the user as command-line arguments.
 */
int main(int argc, char *argv[])
{
	if (argc == 1) {
		fsize(".");
	} else {
		while (--argc > 0) {
			fsize(*++argv);
		}
	}

	return 0;
} /* End main() */

/*
 * fsize	: Display file size and attributes.
 * Input	: name (File or directory name)
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
void fsize(const char *name)
{
	struct stat stbuf;

	/* Retrieve file information */
	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: Cannot access %s\n", name);
		return;
	}

	/* If directory, walk through its contents */
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
		dirwalk(name, fsize);
	}

	/* Print file attributes */
	printf("%8ld %8ld %3lu %4d %4d %c", stbuf.st_ino, stbuf.st_size,
			(unsigned long int)stbuf.st_nlink, stbuf.st_uid, stbuf.st_gid,
			((stbuf.st_mode & S_IFMT) == S_IFDIR) ? 'd' : '-');

	/* Print file permissions */
	printf("%c%c%c%c%c%c%c%c%c ",
			(stbuf.st_mode & S_IRUSR) ? 'r' : '-',
			(stbuf.st_mode & S_IWUSR) ? 'w' : '-',
			(stbuf.st_mode & S_IXUSR) ? 'x' : '-',
			(stbuf.st_mode & S_IRGRP) ? 'r' : '-',
			(stbuf.st_mode & S_IWGRP) ? 'w' : '-',
			(stbuf.st_mode & S_IXGRP) ? 'x' : '-',
			(stbuf.st_mode & S_IROTH) ? 'r' : '-',
			(stbuf.st_mode & S_IWOTH) ? 'w' : '-',
			(stbuf.st_mode & S_IXOTH) ? 'x' : '-');

	printf("%s\n", name);
} /* End fsize() */

/*
 * dirwalk	: Apply a function to all files in a directory.
 * Input	: dir (Directory name), fcn (Function pointer)
 * Author	: Dhruv Ajudiya
 * Created	: 28 November 2024
 * Modified	: 28 November 2024
 */
void dirwalk(const char *dir, void (*fcn)(const char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	/* Open directory */
	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: Cannot open %s\n", dir);
		return;
	}

	/* Iterate through directory entries */
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
			continue;
		}

		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
			fprintf(stderr, "dirwalk: Name %s/%s too long\n", dir, dp->d_name);
		} else {
			snprintf(name, sizeof(name), "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}

	closedir(dfd);
} /* End dirwalk() */
