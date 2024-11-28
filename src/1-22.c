// Exercise 1-23
// Write a program to "fold" long input lines into two or more shorter lines
// after the last non-blank character that occurs before the n-th column of
// input. Make sure your program does something intelligent with very long
// lines, and if there are no blanks or tabs before the specified column.
#include <stdio.h>
#define MAXLINE 1000
#define MAXCOLUMN 12
#define DEBUG 1

void fold(char line[], int maxColumn, char out[]);
int _getline(char s[], int lim);
int is_letter(char c);
void shift_forward(char s[], int i, int amount);

/*
test cases:
./run.sh 1-22 "How now, brown cow. A mystery of sorts in a world of uncertainty."
./run.sh 1-22 "supercalifragilisticexpialidocious"
*/

int main()
{
    char line[MAXLINE];
    char out[MAXLINE];

    if (DEBUG) {
        // marker for easier debugging
        printf("max column: %d\n\n", MAXCOLUMN);
        for (int i = 0; i < MAXCOLUMN-1; ++i) {
            printf(" ");
        }
        printf("%c\n", '*');
    }

    while (_getline(line, MAXLINE) > 0) {
        fold(line, MAXCOLUMN, out);
        printf("%s", out);
    }
}

void fold(char line[], int maxColumn, char out[])
{
    char c;
    int i, col, counter, lastBlank;

    i = col = counter = lastBlank = 0;
    c = line[0];

    for (i = 0; i < MAXLINE-1 && c != '\0'; ++i) {
        c = out[col] = line[i];
        if (c == ' ' || c == '\t') {
            lastBlank = i;
        }
        if (counter == maxColumn) {
            counter = 0;
            out[col+1] = '\n';
            // we're inside a word, revert to last blank
            if (is_letter(c)) {
                if (lastBlank == 0) {
                    out[col] = '\n';
                    i--;
                    counter--;
                } else
                    out[lastBlank] = '\n';
            } 
        }
        col++;
        counter++;
    }
}

int is_letter(char c)
{
    return c >= 'A' && c <= 'z';
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
