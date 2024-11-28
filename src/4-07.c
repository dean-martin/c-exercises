// Exercise 4-7.
// Write a routine ungets(s) that will push back an entire string onto the
// input. Should ungets know about buf and bufp, or should it just use ungetch?
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define SIN     '1'
#define EXP     '2'
#define POW     '3'
#define PRINT   '6'
#define DUPE    '7'
#define SWAP    '8'
#define CLEAR   '9'
#define LAST_PRINT 'L'
#define SET_VARIABLE    '4'
#define POP_VARIABLE    '5'

int getop(char []);
void push(double);
double pop(void);
double peek(void);
void clear(void);
void setvar(char, double);
double getvar(char);

double lastprint = 0;
void printtop(void)
{
    lastprint = peek();
    printf("\t%.8g\n", lastprint);
}

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case SET_VARIABLE:
                setvar(s[0], pop());
                break;
            case POP_VARIABLE:
                push(getvar(s[0]));
                break;
            case NUMBER:
                push(atof(s));
                break;
            case SIN:
                push(sin(pop()));
                break;
            case EXP:
                push(exp(pop()));
                break;
            case POW:
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '%':
                op2 = pop();
                push((int)pop() % (int)op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divsor\n");
                break;
            case PRINT:
                printtop();
                break;
            case LAST_PRINT:
                push(lastprint);
                break;
            case DUPE:
                push(peek());
                break;
            case SWAP:
                op2 = pop();
                double op3 = pop();
                push(op2);
                push(op3);
                break;
            case CLEAR:
                clear();
                break;
            case '\n':
                // nop
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}


double variables[26];

void setvar(char v, double val)
{
    if (!isalpha(v)) {
        printf("error: char '%c' is not alphabetical\n", v);
        return;
    }

    variables['z' - tolower(v)] = val;
}

double getvar(char v)
{
    return variables['z'-tolower(v)];
}

#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void clear(void)
{
    while (sp > 0)
        pop();
}

double peek(void)
{
    if (sp > 0)
        return val[sp-1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);
void ungets(char []);

/* getop: get next operator or numberic operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (isalpha(c)) {
        for (i = 0; isalpha(s[i]); s[++i] = getch())
            ;
        s[i] = '\0';
        if (i == 1) {
            return POP_VARIABLE;
        }
        if (strcmp(s, "lp") == 0)
            return LAST_PRINT;
        if (strcmp(s, "clear") == 0)
            return CLEAR;
        if (strcmp(s, "print") == 0)
            return PRINT;
        if (strcmp(s, "dupe") == 0)
            return DUPE;
        if (strcmp(s, "swap") == 0)
            return SWAP;

        if (strcmp(s, "set") == 0) {
            s[0] = getch();
            s[1] = '\0';
            return SET_VARIABLE;
        }
        if (strcmp(s, "sin") == 0)
            return SIN;
        if (strcmp(s, "exp") == 0)
            return EXP;
        if (strcmp(s, "pow") == 0)
            return POW;
    }

    if (!isdigit(c) && c != '.' && c != '-')
        return c;   /* not a number */

    i = 0;
    if (c == '-') { /* check for negative number or subtraction operation */
        int tmp = getch();
        if (!isdigit(tmp)) {
            ungetch(tmp);
            return c;
        } 
        s[++i] = c = tmp;
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
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

void ungets(char s[])
{
    for (int i = strlen(s)-1; i > 0; i--)
        ungetch(s[i]);
}
