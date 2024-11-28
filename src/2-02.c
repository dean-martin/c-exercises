// Exercise 2-2. 
// Write a loop equivalent to the for loop above without using && or ||.
#include <stdio.h>

int _getline(char s[], int lim);

int main()
{
    char line[1000];

    while (_getline(line, 1000) > 0)
        printf("%s", line);

    return 0;
}

// _getline: read a line into s, return length
int _getline(char s[], int lim) 
{
    int c, i;

    for (i = 0; i < lim-1; ++i) {
        c = getchar();

        if (c == EOF)
            return i;

        s[i] = c;

        if (c == '\n') {
            s[++i] = '\0';
            return i;
        }
    }

    return i;
}
