// Exercise 5-11.
// Modify the programs entab and detab (written as exercises in Chapter 1) to
// accept a list of tab stops as arguments. Use the default tab settings if
// there are no argumegnts.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "common.c" // for _getline

#define MAXLINE 1000
#define TABSTOP 4
#define BUFFERSIZE 5000

void tabstop(char *s, const int tabstop);
void shift(char s[], int start, int amount);

// detab: replaces tabs with the proper number of blanks to the next tabstop.
int main(int argc, char **argv) 
{
    char line[MAXLINE];
    char line_buffer[BUFFERSIZE];

    int c, tbstop = TABSTOP;

    while (--argc > 0 && (*++argv)[0] == '-') {
        int c;
        while (c = *++argv[0])
            switch (c) {
                case 't':
                    int n = 0;
                    while (isdigit(c = *++(*argv))) {
                        n = (n * 10) + c-'0';
                    }
                    tbstop = n;
                break;
            }
    }

    while(_getline(line, MAXLINE) > 0) {
        // todo: fix tbstop-1 to just tbstop
        tabstop(line, tbstop-1);
        strcat(line_buffer, line);
    }

    printf("%s", line_buffer);

    return 0;
}

void tabstop(char *s, const int ts) 
{
    char c;
    int i;
    for (i = 0; (c = s[i]) != '\0'; i++) {
        if (c == '\t') {
            shift(s, i, ts);
            for(int j = i; j <= i + ts; j++) {
                s[j] = 't';
            }
        }
    }
}

void shift(char s[], int start, int amount) 
{
    char c, swap;
    
    for (int i = strlen(s); i > start; i--) {
        c = s[i];
        s[i+amount] = c;
    }
}
