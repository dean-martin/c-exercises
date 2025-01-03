// Exercise 6-2.
// Write a program that reads a C program and prints in alphabeti-
// cal order each group of variable names that are identical in the first 6 charac-
// ters, but different somewhere thereafter. Don't count words within strings and
// comments. Make 6 a parameter that can be set from the command line.
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "common.c"

#define MAXWORD 100

struct tnode {
    char *prefix;
    char *words[25];
    int buf;
    struct tnode *left;
    struct tnode *right;
};
struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

char *strdup(const char *);
int getword(char *, int);

unsigned int n = 5;

/* word frequency count */
int main(int argc, char *argv[])
{
    while (--argc > 0 && (*++argv)[0] == '-') {
        int c;
        while ((c = *++argv[0]))
            switch (c) {
                case 'n': {
                    int nn = 0;
                    while (isdigit(c = *++argv[0]))
                        nn = (nn * 10) + (c-'0');
                    n = nn;
                } break;
            }
    }

    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && strlen(word) >= n)
            root = addtree(root, word);
    treeprint(root);

    return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->prefix = strndup(w, n);
        p->words[p->buf++] = strdup(w);
        p->left = p->right = NULL;
        return p;
    } else if ((cond = strncmp(w, p->prefix, n)) == 0) {
        p->words[p->buf++] = strdup(w);
    } else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("[%s] ", p->prefix);
        char **w = p->words;
        while (*w) {
            printf("%s ", *w++);
        }
        printf("\n");
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(const char *s)    /* make a duplicate of s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1);    /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
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

        if (c == '"') // skip string words
            while ((c = getch()) != '"' || c == EOF)
                ;

        if (c == '/') {
            c = getch();
            if (c == '*') { // inside a multi-line comment
                int prev = c;
                while (!(c == '/' && prev == '*') || c == EOF)
                    prev = c, c = getch();
            } else if (c == '/') { // on a java style comment, skip to \n
                // advance until \n or EOF
                while ((c = getch()) != '\n' || c == EOF)
                    ;
            } else {
                ungetch(c);
            }
        }

        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}
