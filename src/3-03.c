// Exercise 3-3.
// Write a function expand(s1,s2) that expands shorthand notations like a-z in
// the string s1 into the equivalent complete list abc...xyz in s2. Allow for
// letters of either case and digits, and be prepared to handle cases like
// a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken
// literally.
#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]);
void test(char s1[], char out[]);

int main()
{
    char out[100];
    test("a-z", out);
    test("0-9", out);
    test("a-z0-9", out);
    test("-a-z", out);
    test("-a-z-", out);
    test("a-b-c", out);
    test("a-c and x-z", out);
    test("a-c 2-8 x-z", out);
}

void expand(char s1[], char s2[])
{
    char c, prev;
    int i,j;
    for (i = 0, j = 0; prev = c, (c = s1[i]) != '\0'; i++) {
        char end = s1[i+1];

        if (isalnum(c) || isspace(c)) {
            s2[j++] = c;
        }

        if (i == 0 && c == '-')
            s2[j++] = c;

        if (s1[i+1] == '\0' && c == '-')
            s2[j++] = c;


        if (isalnum(prev) && c == '-' && isalnum(end)) {
            for (int k = prev+1; k < end; k++) {
                s2[j++] = k;
            }
        }
    }
    s2[j] = '\0';
}

void test(char s1[], char out[])
{
    expand(s1, out);
    printf("%s: %s\n", s1, out);
}
