// Exercise 3-6.
// Write a version of itoa that accepts three arguments instead of two. The
// third argument is a minimum field width; the converted number must be padded
// with blanks on the left if necessary to make it wide enough.
#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[], int minwidth);
void reverse(char s[]);
void binprintf(int v);


void test(int n, int width)
{
    char out[100];
    itoa(n, out, width);
    printf("%s\n", out);
}

int main()
{
    test(2, 10);
    test(-5000, 20);
    test(-5000, 5);
    test(-5000, 6);

    unsigned bignegative = (-INT_MAX)-1;
    //binprintf(bignegative);

    test(bignegative, 30);
    test(bignegative+1, 5);
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int minwidth)
{
    int i;
    int sign = 1;
    if (n < 0) /* record sign */
        sign = -1;
    i = 0;
    do { /* generate digits in reverse order */
        s[i++] = (n % 10)*sign + '0';  /* get next digit */
    } while ((n /= 10) != 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    while (i < minwidth)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

void binprintf(int v)
{
    unsigned int mask=1<<((sizeof(int)<<3)-1);
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
    printf(": %i\n", v);
}
