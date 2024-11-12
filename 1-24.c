// Exercise 1-24.
// Write a program to check a C program for rudimentary syntax errors like
// unbalanced parentheses, brackets and braces. Don't forget about quotes, both
// single and double, escape sequences, and comments. (This program is hard if
// you do it in full generality.)
#include <stdio.h>
#define MAXLINE 1000

enum pair { CURLIES, BRACKETS, PARENS, SINGLES, DOUBLES };
enum comment_state { OUT, IN };

// TODO: escape sequences & comments

void syntax_check(char line[]);
int _getline(char s[], int lim);

/*
./run.sh 1-24 "$(cat unbalanced-pairs.c)"
*/

/*
{}} // should be ignored now
*/

int balance[7];
int state = OUT;

int main()
{
    char line[MAXLINE];

    while (_getline(line, MAXLINE) > 0) {
        syntax_check(line);
    }
    int i;
    for (i = 0; i < 7; ++i)
        if(balance[i] != 0)
            printf("unbalanced pairs");
}

void syntax_check(char line[])
{
    char c, prev;
    int i;

    // A more sophiscated approach that gives line and column on would be 
    // useful, this is way easier and "rudimentary" though.

    for (i = 0; (c = line[i]) != '\0'; ++i) {
        if (prev = '/' && c == '*')
            state = IN;
        if (prev == '*' && c == '/')
            state == OUT;
        if (state == IN)
            continue;

        if (c == '{')
            balance[CURLIES]++;
        if (c == '}')
            balance[CURLIES]--;

        if (c == '[')
            balance[BRACKETS]++;
        if (c == ']')
            balance[BRACKETS]--;

        if (c == '(')
            balance[PARENS]++;
        if (c == ')')
            balance[PARENS]--;

        prev = c;
    }
}

// _getline: read a line into s, return length
int _getline(char s[], int lim) 
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}
