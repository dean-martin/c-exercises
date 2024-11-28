// Exercise 3-5.
// Write the function itob(n,s,b) that converts the integer n into a base b
// character representation in the string s. In particular, itob(n,s,16) formats
// n as a hexadecimal integer in s.
#include <stdio.h>
#include <math.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);
void test(int i, char s[], int b);

int main()
{
    char out[100];

    test(9, out, 2);
    test(10, out, 2);
    test(12, out, 2);
    test(12, out, 10);

    test(9, out, 16);
    test(10, out, 16);
    test(13, out, 16);
    test(16, out, 16);
    
    return 0;
}

void test(int i, char s[], int b)
{
    itob(i, s, b);
    printf("%s %i\n", s, i);
}

char gethexdigit(int digit)
{
    if (digit > 9) {
        return 'A' + digit - 10;
    }

    return digit + '0';
}

void itob(int n, char s[], int b)
{
    int i = 0;
    do {
        int digit = n % b;
        if (b == 16) {
            s[i++] = gethexdigit(digit);
        } else {
            s[i++] = digit + '0';
        }

    } while ((n /= b) != 0);
    if (b == 16) {
        s[i++] = 'x';
        s[i++] = '0';
    }
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
