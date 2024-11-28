// Exercise 5-6.
// Rewrite appropriate programs from earlier chapters and exercises with
// pointers instead of array indexing. Good possibilities include getline
// (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4),
// reverse (Chapter 3), and strindex and getop (Chapter 4).
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define SIN     '1'
#define EXP     '2'
#define POW     '3'

int _getline(char s[], int lim);
void itoa(int n, char *s);
void reverse(char *s);
void reverser(char *s, char *t);
int strindex(char s[], char t[]);
int strindex_( char *s,  char *t);
int getch(void);
void ungetch(int);
int getop(char s[]);

int main()
{
    /*
    char ns[MAXLINE] = "";
    itoa(-45, ns);
    printf("%s\n", ns);

    char rev[MAXLINE] = "hello";
    reverse(rev);
    printf("%s\n", rev);
    */

    //printf("%i\n", strindex("hello", "lo"));
    printf("%i\n", strindex_("hello", "lo"));

    //printf("%i\n", strindex("hello", "hel"));
    printf("%i\n", strindex_("hello", "el"));
    

    if (1) {
        int type;
        char s[MAXOP];
        while ((type = getop(s)) != EOF)
            printf("getop: %i\n", type);

    return 0;
    }

    char s[MAXLINE] = "";
    int i = 0;
    while ((i = _getline(s, MAXLINE)) > 0) {
        printf("%s", s);
    }
}

int _getline(char *s, int lim)
{
    char *start = s;
    int c;

    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s == '\0';
    return s - start;
}

void itoa(int n, char *s)
{
    if (n < 0) {
        *s++ = '-';
        *s = '\0';
        n = -n;
    }
    if (n / 10)
        itoa(n / 10, s);
    s += strlen(s);
    *s++ = n % 10 + '0';
    *s = '\0';
}

void reverse(char *s)
{
    reverser(s, s+strlen(s)-1);
}

void reverser(char *s, char *t)
{
    if (s == t)
        return;
    int c;
    c = *s, *s++ = *t, *t-- = c;
    reverser(s, t);
}

int strindex_(char *s, char *t)
{
    for (int i = 0; *s; i++, s++) {
        char *tt = t;
        char *ss = s;
        while (*tt && *ss++ == *tt)
            tt++; // must happen after because we can go into weird memory land, hence the *tt precheck
        if (*tt == '\0')
            return i;
    }
    return -1;
}

int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
         for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

#include <ctype.h>

/* getop: get next operator or numberic operand */
int getop(char *s)
{
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t')
        ;
    *(s+1) = '\0';

    if (isalpha(c)) {
        while (isalpha(*s))
            *(++s) = getch();
        *s = '\0';
        if (strcmp(s, "sin") == 0)
            return SIN;
        if (strcmp(s, "exp") == 0)
            return EXP;
        if (strcmp(s, "pow") == 0)
            return POW;
    }

    if (!isdigit(c) && c != '.' && c != '-')
        return c;   /* not a number */

    if (c == '-') { /* check for negative number or subtraction operation */
        int tmp = getch();
        if (!isdigit(tmp)) {
            ungetch(tmp);
            return c;
        } 
        *(++s) = c = tmp;
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(*(++s) = c = getch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(*(++s) = c = getch()))
            ;
    *s = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
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
