// Exercise 5-1.
// As written, getint treats a + or - not followed by a digit as a valid
// representation of zero. Fix it to push such a character back on the input.
#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);
int getint(int *pn);

int main()
{
    int *pn;
    int i = 0;
    while ((i = getint(pn)) != EOF)
        if (i > 0) // is a number
            printf("%i\n", *pn);
    
    return 0;
}

/* Our version of getint returns EOF for end of file, zero if the next input is
   not a number, and a positive value if the input contains a valid number. */
/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int tmp = getch();
        if (!isdigit(tmp)) {
            ungetch(c);
            return 0;
        }
        c = tmp;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
