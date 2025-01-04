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

unsigned hash(char *);
struct nlist *lookup(char *s);
struct nlist *install(char *, char *);
void undef(char *);

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

int main()
{
    if (install("deez", "nutz") == NULL) {
        printf("node not allocated\n");
        return -1;
    }

    undef("deez");

    struct nlist *node = lookup("deez");
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
    struct nlist *np, *prev = NULL;
    unsigned hashval;
    prev = NULL; // THIS WAS CAUSING THE SEGFAULT XD
    // it's an auto variable, so it's filled with garbage, and somehow weirdness was happening?

    hashval = hash(name);

    for (np = hashtab[hashval]; np != NULL; np = np->next) {
        if (strcmp(name, np->name) == 0)
            break;
        prev = np;
    }
    if (np != NULL) {
        if (prev == NULL) {
            hashtab[hashval] = np->next; // first on the list, put np->next on top
        } else {
            prev->next = np->next; // somewhere in middle, patch list
        }
        free((void *) np->name);
        free((void *) np->defn);
        free((void *) np);
    }
}
