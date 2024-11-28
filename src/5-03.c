// Exercise 5-3.
// Write a pointer version of the function strcat that we showed in Chapter 2;
// strcat(s,t) copies the string t to the end of s.
#include <stdio.h>
#define MAXSIZE 1000

void pstrcat(char *, char *);
void _strcat(char[], char[]);

int main()
{
    char s[MAXSIZE] = "Hello, ";
    pstrcat(s, "world!");

    printf("%s\n", s);

    char s2[MAXSIZE] = "";
    pstrcat(s2, "henlo!");

    printf("%s\n", s2);

    return 0;
}


void pstrcat(char *s, char *t)
{
    if (*s) // not empty, i.e. already at \0
        while (*++s) // move s to it's end \0
            ;
    while (*s++ = *t++)
        ;
}

/* strcat: concatenate t to end of s; s must be big enough */
void _strcat(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')    /* find end of s */
        i++;
    while ((s[i++] = t[j++]) != '\0')   /* copy t */
        ;
}
