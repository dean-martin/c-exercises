// Exercise 8-1.
// Rewrite the program cat from Chapter 7 using read, write,
// open and close instead of their standard library equivalents. Perform experi-
// ments to determine the relative speeds of the two versions.

// see: https://www.man7.org/linux/man-pages/man0/unistd.h.0p.html
#include <unistd.h> // universal std.h (POSIX definitions)
#include <fcntl.h> // open(char *name, mode, perms);

#define EOF -1 // TODO figure out where EOF is defined in POSIX headers

int getchar(void);

int main(int argc, char *argv[])
{
	// simple cat prog
	char c;

	while ((c = getchar()) != EOF)
		write(1, &c, 1);

	return 0;
}

int getchar(void)
{
	char c;

	// casting to unsigned exlimnates any problem of sign extension.
	return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}
