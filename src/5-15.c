// Exercise 5-15.
// Add the option -f to fold upper and lower case together, so that
// case distrinctions are not made during sorting; for example, a and A compare
// equal.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.c"

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));
int numcmp(char *, char *);

// this is so whack i love it
// if i learned structs, i could make a wrapper, would be really cool.
int (*torevcmp)(void *, void *) = NULL;
int revcmp(void * a, void * b)
{
    if (torevcmp == NULL)
        return 0; // nop

    // do the opposite
    int res = torevcmp(a, b);
    if (res > 0)
        return -1;
    if (res < 0)
        return 1;
    return 0;
}

int ignorecase = 0;

int _strcmp(char *a, char *b)
{
    if (ignorecase) {

    }
    return strcmp(a, b);
}

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;      /* number of input lines read */
    int numeric = 0;
    int reverse = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        int c;
        while ((c = *++argv[0]))
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                break;
            }
    }
    printf("numeric: %d\n", numeric);
    printf("reverse: %d\n", reverse);

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        int (*cmp)(void *, void *) = (int (*)(void*,void*))(numeric ? numcmp : strcmp);
        if (reverse) {
            torevcmp = cmp;
            cmp = revcmp;
        }
        _qsort((void **) lineptr, 0, nlines-1,
              cmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void _qsort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)      /* do nothing if array contains */
        return;             /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    _qsort(v, left, last-1, comp);
    _qsort(v, last+1, right, comp);
}

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[maxlines];

    nlines = 0;
    while ((len = _getline(line, maxlines)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
