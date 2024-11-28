// Exercise 5-5.
// Write versions of the library functions strncpy, strncat, and strncmp, which
// operate on at most the first n characters of their argument strings. 
// For example, strncpy(s,t,n) copies at most n characters of t to s. 
// Full descriptions are in Appendix B.
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

char *_strncpy(char *s, char *t, int n);
char *_strncat(char *s, const char *ct, int n);
int _strncmp(const char *cs, const char *ct, int n);

int main()
{
    char s[MAXLINE] = "hello";
    char *r = _strncpy(s, "world", 5);
    printf("%s\n", r);

    char *r2 = _strncat(s, "one", 2);
    printf("%s\n", r2);

    printf("%i\n", _strncmp("hello, world!!", "hello, world!", 25)); // 0 >
    printf("%i\n", _strncmp("hello, world!", "hello, world!", 25)); // cs==ct
    printf("%i\n", _strncmp("hi", "hello", 1));  // 'h'-'h'
    printf("%i\n", _strncmp("hi", "hello", 2));  // 'i'-'e'
}

/* 
char *strncpy(s,ct,n) copy at most n characters of string ct to s; return s.
Pad with '\0's if t has fewer than n characters.
*/
char *_strncpy(char *s, char *ct, int n)
{
    char *start = s;
    int i = 0;
    for (i = 0; i < n; i++)
        if (*ct == '\0')
            *s++ = '\0';
        else
            *s++ = *ct++;
    s = start;

    return s;
}

/* 
concatenate at most n characters of string ct to string s, terminate s with '\0';
return s;
*/
char *_strncat(char *s, const char *ct, int n)
{
    char *start = s;
    s += strlen(s);
    for (int i = 0; i < n && *ct != '\0'; i++)
        *s++ = *ct++;

    s = start; // reset position

    return s;
}

/*
compare at most n characters of string cs to string ct;
return <0 if cs<ct, 0 if cs==cs, or >0 if cs>ct.
*/
int _strncmp(const char *cs, const char *ct, int n)
{
    int i = 0;
    for (; *cs == *ct && i < n-1; i++, *cs++, *ct++)
        if (*cs == '\0')
            return 0;
    return *cs - *ct;
}
