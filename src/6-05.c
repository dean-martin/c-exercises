// Exercise 6-05.
// Write a function undef that will remove a name and definition
// from the table maintained by lookup and install.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct nlist {          /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

#define HASHSIZE 101

struct nlist *lookup(char *s);
struct nlist *install(char *, char *);
void undef(char *);

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

int main()
{
    struct nlist *node = install("deez", "nutz");
    if (node == NULL) {
        printf("node not allocated\n");
        return -1;
    }

    node = lookup("deez");
    printf("%s: %s\n", node->name, node->defn);

    undef("deez");
    node = lookup("deez");
    if (node) {
        printf("still alive!\n");
    } else {
        printf("deleted!\n");
    }
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval & HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;    /* found */
    return NULL;          /* not found */
}

struct nlist *lookup(char *s);
char *strdup(const char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {    /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else        /* already there */
        free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name)
{
    struct nlist *np;
    struct nlist *prev;
    unsigned hashval;

    hashval = hash(name);

    // I got this correct, but the book organized the code way cleaner, going to change to.
    // also, my free(np); is segfaulting and I don't know why.
    for (np = hashtab[hashval]; np != NULL; prev = np, np = np->next)
        if (strcmp(name, np->name) == 0) {
            if (np && np->next) {
                if (prev == NULL) {
                    hashtab[hashval] = np->next; // first on the list, put np->next on top
                } else {
                    prev->next = np->next; // somewhere in middle, patch list
                }
            }
            free((void *)np->name);
            free((void *)np->defn);
            // segfaulting below, why?
            free((void *)np);
            return;
        }
}
