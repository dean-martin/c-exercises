#include <stdio.h>
#include <stdlib.h>
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

void setgetch(char *expr);

double evaluate(char *expr)
{
    int type;
    double op2;
    char s[MAXOP];

    setgetch(expr);

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
            case '\n':
                // nop
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return pop();
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
char getchstr[MAXOP];

// hack our way in! :D
void setgetch(char *s)
{
    strncpy(getchstr, s, MAXOP);
}

int getch(void) /* get a (possibly pushed back) character */
{
    static char *getchs = getchstr;
    if (bufp > 0)
        return buf[--bufp];
    else if (*getchs)
        return *getchs++;

    else
        return getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

