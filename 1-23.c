// Exercise 1-23.
// Write a program to remove all comments from a C program.
// Don't forget to handle quoted strings and character constants properly. 
// C comments do not nest.
#include <stdio.h>
#define MAXLINE 1000
#define IN 1
#define OUT 0

void remove_comments(char s[], char out[]);
int _getline(char s[], int lim);

/*
./run.sh 1-23 "$(cat 1-23.c)"
*/

int state = OUT;

int main()
{
    char line[MAXLINE];
    char out[MAXLINE];
    while(_getline(line, MAXLINE) > 0) {
        remove_comments(line, out);
        printf("%s", out);
    }

    return 0;
}

/* single line normal comment */
;
/* multiline comment
;
*/

char blah; /* blahblah */ char shouldstay2; char dangit;

void remove_comments(char s[], char out[]) //here i am!
{
    int i, ci = 0; // test1
    char c;
    char prev; /* another test comment */

    for (i = 0; (c = s[i]) != '\0'; ++i) { // test2

        if (prev == '/' && c == '/') {
            out[ci-1] = '\n';
            break;
        }

        if (prev == '/' && c == '*' && state == OUT) {
            out[ci-1] = '\n';
            state = IN;
        }

        if (state == OUT) {
            out[ci] = c;
            ci++;
        }

        if (prev == '*' && c == '/') {
            state = OUT;
        }

        prev = c;
    }
    out[ci] = '\0';
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
