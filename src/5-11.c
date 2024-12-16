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

void detab(char *s, const int tabstop);
void shift(char s[], int start, int amount);
void entab(char s[]);
void slice(char s[], int start, int stop);

char line[MAXLINE];
char line_buffer[BUFFERSIZE];

// entab: replaces strings of blanks by the minimum number of tabs and blanks
// to achieve the same spacing.
// detab: replaces tabs with the proper number of blanks to the next tabstop.
int main(int argc, char **argv) 
{
    int c, tabstop = TABSTOP;

    while (--argc > 0 && (*++argv)[0] == '-') {
		int c;
		while ((c = *++argv[0]))
            switch (c) {
                case 't':
                    int n = 0;
                    while (isdigit(c = *++argv[0])) {
                        n = (n * 10) + c-'0';
                    }
                    tbstop = n;
                break;
            }
    }

    while(_getline(line, MAXLINE) > 0) {
		// todo: fix tbstop-1 to just tbstop
		detab(line, tabstop-1);
		// entab(line);
		strcat(line_buffer, line);
	}

    printf("%s", line_buffer);

    return 0;
}

void entab(char s[])
{
		int i, blank_start = 0, blank_count = 0;
		char c, prev;
		for(i = 0; (c = s[i]) != '\0'; i++) {
				if (c == ' ') {
						blank_count++; 
						if (prev != ' ')
								blank_start = i;
				} 
				else 
						blank_count = 0;

				if (blank_count == TABSTOP) {
						slice(s, blank_start, i);
						s[blank_start] = '\t';
						blank_count = 0;
						i = blank_start;
						prev = s[i];
				}
				else
						prev = c;
		}
}

void slice(char s[], int start, int end) {
		char c;
		int i = start;
		int shift = end - start;
		for(; (c = s[i]) != '\0'; i++) {
				s[i] = s[i + shift];
		}
}

void detab(char *s, const int ts) 
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
