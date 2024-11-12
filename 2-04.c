/* 
Exercise 2-4. 
 Write an alternate version of squeeze(s1,s2) that deletes each character in
 s1 that matches any character in the string s2.
*/
#include <stdio.h>

void squeeze(char s[], int c);
void string_squeeze(char s[], char set[]);

int main()
{
    char s[] = "hello world";
    printf("%s\n", s);
    squeeze(s, 'h');
    printf("%s\n", s);

    char s2[] = "hello, world";
    string_squeeze(s2, "ho");
    printf("%s\n", s2);


    return 0;
}

// string cheese!
void string_squeeze(char s[], char set[])
{
    char c;
    for (int i = 0; (c = set[i]) != '\0'; i++) {
        squeeze(s, c);
    }
}

/* squeeze: delete all c from s */
void squeeze(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}
