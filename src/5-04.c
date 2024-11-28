// Exercise 5-4.
// Write the function strend(s,t), which returns 1 if the string t occurs at
// the end of the string s, and zero otherwise.
#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main()
{
    printf("%i\n", strend("hello, world!", "world!"));
    printf("%i\n", strend("hello, xorld!", "world!"));
    printf("%i\n", strend("hello, world!", "world"));
}

int strend(char *s, char *t)
{
    char *r = t; // marker to test if *t was full reset to start address
    s += strlen(s);
    if (*t) // this works as well, strlen is more concise
        while (*++t)
            ;
    
    while (*s-- == *t--)
        if (t == r && *s == *t)
            return 1;

    return 0;
}
