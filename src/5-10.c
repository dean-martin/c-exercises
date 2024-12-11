// Exercise 5-10.
// Write the program expr, which evaluates a reverse Polish
// expression from the command line, where each operator or operand is a separate
// argument. For example,
//      expr  2  3  4  +  *
// evaluates 2 x (3+4).
#include <stdio.h>
#include "common.c"
#include "polishcalculator.c"

/*
bash -c 'set -f; ./run.sh 5-10 2 3 4 + *;'
*/

void parse_expr(int argc, char **argv, char *s)
{
    while (--argc > 0 && *++argv) {
        while (**argv) {
            char c = *(*argv)++;
            *s++ = c;
        }
        *s++ = ' ';
    }
    *s++ = EOF;
    *s = '\0';
}

int main(int argc, char **argv)
{
    char expr[MAXOP];
    parse_expr(argc, argv, expr);
    printf("expr: %s\n", expr);
    printf("result: %g\n", evaluate(expr));

    return 0;
}

int _main(int argc, char **argv)
{
    int c = 0;
    printf("argc: %i\n", argc);
    while (--argc > 0 && *(*++argv) == '-') {
        //printf("%c\n", *++argv[0]);
        //printf("%c\n", *++(argv[0]));
        while (c = *++argv[0])
            printf("'%c'", c);
        printf("\n");
    }

    return 0;

    while (--argc > 0)
        printf((argc > 1) ? "%s " : "%s", *++argv);
    printf("\n");
    return 0;
}
