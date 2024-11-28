// Exercise 2-3. 
// Write the function htoi(s), which converts a string of hexadecimal digits
// (including an optional 0x or 0X) into its equivalent integer value. The
// allowable digits are 0 through 9, a through f, and A through F.
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAXLINE 1000

void test(char s[], int expected);
int htoi(char s[]);
void parsehexstr(char s[], char out[MAXLINE]);
int hextodec(char c);

int main()
{
    test("7", 0x7);
    test("0x7", 0x7);
    test("0X17", 23);
    test("2C7", 711);
    test("0X2FF", 767);
    test("c_is_cool", -1); // should error
    test("hi", -1); // should error

    return 0;
}

void test(char s[], int expected)
{
    int res = 0;
    if ((res = htoi(s)) != expected)
        printf("failure: htoi(%s) == %i != 0x%x\n", s, res, expected);
    else 
        printf("success: htoi(%s) == %i == 0x%x\n", s, res, expected);
}

// is it possible to be declared automatic and initialize a garbage filled char array?
// i imagine when we get to memory we can do stuff like that.
char out[MAXLINE];

int htoi(char s[])
{
    parsehexstr(s, out);

    int len;
    for (len = 0; out[len] != '\0'; ++len)
        ;
    len--;

    char c;
    int n = 0;
    for (int i = 0; (c = out[i]) != '\0'; ++i) {
        int hex = hextodec(c);
        if (hex == -1) {
            printf("error: unexpected char '%c' ", c);
            return -1;
        }
        n += hex * pow(16, len);
        len--;
    }

    return n;
}

int hextodec(char c)
{
    if (!isalnum(c))
        return -1;

    if (islower(c) && c-'a'+10 <= 15)
        return c-'a'+10;

    if (isupper(c) && c-'A'+10 <= 15)
        return c-'A'+10;

    if (isdigit(c))
        return c-'0';

    return -1;
}

void parsehexstr(char s[], char out[])
{
    char c, prev;
    int offset = 0;
    int ci = 0;
    if (s[0] == '0' && tolower(s[1]) == 'x')
        offset = 2;

    for (int i = 0+offset; (c = s[i]) != '\0'; ++i) {
        out[ci++] = tolower(c);
        prev = c;
    }
}
