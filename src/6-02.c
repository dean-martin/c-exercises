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

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct pnode {
    char *prefix;
    char *words[25];
    int buf;
    struct pnode *left;
    struct pnode *right;
};

#define MAXWORD 100

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *);
char *strdup(const char *);

void treeprint(struct tnode *);
int getword(char *, int);

unsigned int n = 5;

struct pnode *_addtree(struct pnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = (struct pnode *) malloc(sizeof(struct pnode));
        p->prefix = strndup(w, n);
        p->words[p->buf++] = strdup(w);
        p->left = p->right = NULL;
        return p;
    } else if ((cond = strncmp(w, p->prefix, n)) == 0) {
        p->words[p->buf++] = strdup(w);
    } else if (cond < 0)
        p->left = _addtree(p->left, w);
    else
        p->right = _addtree(p->right, w);

    return p;
}

void _treeprint(struct pnode *p)
{
    if (p != NULL) {
        _treeprint(p->left);
        printf("[%s] ", p->prefix);
        char **w = p->words;
        while (*w) {
            printf("%s ", *w++);
        }
        printf("\n");
        _treeprint(p->right);
    }
}

/* word frequency count */
int main()
{
    struct pnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && strlen(word) >= n)
            root = _addtree(root, word);
    // TODO: ignore comment & string words.
    // TODO: make prefix size cmdline parameter.
    // I thought I had to sort the tree to print it alphabetically,
    // but the recursive descent does that by nature. Excellent.
    _treeprint(root);

    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

#include <stdlib.h>

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
