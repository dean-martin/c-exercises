// Exercise 3-4.
// In a two's complement number representation, our version of itoa does not
// handle the largest negative number, that is, the value of n equal to
// -(2^wordsize-1). Explain why not. Modify it to print that value correctly,
// regardless of the machine on which it runs.
#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);
void binprintf(int v);

int main()
{
    char out[100];
    itoa(42, out);
    printf("%s\n", out);

    itoa(-42, out);
    printf("%s\n", out);

    unsigned bignegative = (-INT_MAX)-1;
    binprintf(bignegative);

    itoa(bignegative, out);
    printf("%s\n", out);

    itoa(bignegative+1, out);
    printf("%s\n", out);
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i;
    int sign = 1;
    if (n < 0) /* record sign */
        sign = -1;
    i = 0;
    do { /* generate digits in reverse order */
        s[i++] = (n % 10)*sign + '0';  /* get next digit */
    } while ((n /= 10) != 0);    /* delete it */
    // because the largest negative number is -256 to 255, 
    // trying to turn -256 * -1 will result in -256 because of an overflow.
    if (sign < 0)
        s[i++] = '-';
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
