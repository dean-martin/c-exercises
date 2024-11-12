// Exercise 2-5. 
// Write the function any(s1,s2), which returns the first location in the
// string s1 where any character from the string s2 occurs, or -1 if s1
// contains no characters from s2. (The standard library function strpbrk does
// the same job but returns a pointer to the location.)
#include <stdio.h>

int any(char s1[], char s2[]);
int has_char(char s1[], char c);

int main()
{
    printf("hello, world\n");
    char s[] = "hello, world";
    printf("%s: pos: %d\n", s, any(s, "oe"));
    printf("%s: pos: %d\n", s, any(s, "eo"));
    printf("%s: pos: %d\n", s, any(s, "eoh"));
    printf("%s: pos: %d\n", s, any(s, "d"));
    return 0;
}

int any(char s1[], char s2[])
{
    char c;
    int res = -1;
    for (int i = 0; (c = s2[i]) != '\0'; i++) {
        int t = has_char(s1, c);
        if (t >= 0 && (t < res || res == -1))
             res = t;
    }
    return res;
}

int has_char(char s1[], char c)
{
    char ch;
    for (int i = 0; (ch = s1[i]) != '\0'; i++) {
        if (ch == c)
            return i;
    }

    return -1;
}
