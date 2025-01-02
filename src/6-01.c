// Exercise 6-1.
// Our version of getword does not properly handle underscores,
// string constants, comments or preprocessor control lines. Write a better ver-
// sion.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "common.c" // getch, ungetch

#define MAXWORD 100

struct key {
    char *word;
    int count;
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

struct key keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    // . . .
    "unsigned", 0,
    "void", 0,
    "volatile", 0, // when was this a keyword?
    "while", 0
};

// #define NKEYS (sizeof keytab / sizeof(struct key))
// This (below) has the advantage that it does not need to be changed if the type changes.
#define NKEYS (sizeof keytab / sizeof keytab[0])

/* count C keywords */
int main()
{
    int n;
    char word[MAXWORD];

    printf("NKEYS: %lu\n", NKEYS);

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n -1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}
