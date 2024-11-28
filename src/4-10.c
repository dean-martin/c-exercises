// Exercise 4-10.
// An alternate organization uses getline to read an entire input line; this
// makes getch and ungetch unnecessary. 
// Revise the calculator to use this approach.
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXLINE 1000
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
int _getline(char s[], int lim);

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

int line_i = 0;
char line[MAXLINE];

/* getop: get next operator or numberic operand */
int getop(char s[])
{
    if (strlen(line) == 0 || strlen(line) == line_i)
        if (_getline(line, MAXLINE) == 0)
            return EOF;
        else 
            line_i = 0;

    int i, c;

    while ((s[0] = c = line[line_i++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (isalpha(c)) {
        for (i = 0; isalpha(s[i]); s[++i] = line[line_i++])
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
            s[0] = line[line_i++];
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
        int tmp = line[line_i++];
        if (!isdigit(tmp)) {
            line[--line_i] = tmp;
            return c;
        } 
        s[++i] = c = tmp;
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = line[line_i++]))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = line[line_i++]))
            ;
    s[i] = '\0';
    if (c != EOF)
        line[--line_i] = c;
    return NUMBER;
}

// _getline: read a line into s, return length
int _getline(char s[], int lim) {
  int c, i;

  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

