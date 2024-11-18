// Exercise 4-13.
// Write a recursive version of the function reverse(s), which reverses the
// string s in place.
#include <stdio.h>
#include <string.h>

void reverse(char[]);
void reverser(char[], int i, int len);

int main()
{
    char s[] = "hello, world!";
    printf("%s\n", s);
    
    reverse(s);
    printf("%s\n", s);

    reverse(s);
    printf("%s\n", s);

    char s2[] = "h";
    reverse(s2);
    printf("%s\n", s2);

    return 0;
}

// originally did this with a static index, was trying to avoid using
// any index here. Looking up the book solutions, 
// they use a helper function that keeps indexes. 

void reverse(char s[])
{
    reverser(s, 0, strlen(s)-1);
}

void reverser(char s[], int i, int len)
{
    if (i > len)
        return;
    int c;
    c = s[i], s[i] = s[len], s[len] = c;
    reverser(s, i+1, len-1);
}
