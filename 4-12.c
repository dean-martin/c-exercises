// Exercise 4-12.
// Adapt the ideas of printd to write a recursive version of itoa; that is,
// convert an integer into a string by calling a recursive routine.
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

void printd(int n);
void itoa(int, char[]);
void itoa_s(int, char[]);

int main()
{
    char out[MAXLINE] = {'\0'};

    itoa(-2, out);
    printf("%s\n", out);

    out[0] = '\0'; // reset
    itoa(-123, out);
    printf("%s\n", out);

    out[0] = '\0'; // reset
    itoa(123, out);
    printf("%s\n", out);

    return 0;
}

// originally wrote this with a static int index, but that isn't "true" recursion.
// after looking up the answer for 4-13, they used a helper function here in 4-12.
// This solution works, but needs the string to be "reset" to avoid appended output.

void itoa(int n, char s[])
{
    int i = strlen(s);
    if (n < 0) {
        s[i++] = '-';
        s[i] = '\0';
        n = -n;
    }
    if (n / 10)
        itoa(n / 10, s);
    i = strlen(s);
    s[i++] = n % 10 + '0';
    s[i] = '\0';
}

/* printd: print n in decimal */
void printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}
