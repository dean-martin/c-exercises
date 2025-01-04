
union u_tag {
    int ival;
    float fval;
    char *sval;
} u;

#define NSYM 1
struct {
    char *name;
    int falgs;
    int utype;
    union {
        int ival;
        float fval;
        char *sval;
    } u;
} symtab[NSYM];

typedef int int32;
typedef unsigned int uint; // hehe

typedef struct tnode *Treeptr;

typedef struct tnode {
    char *word;
    int count;
    Treeptr left;
    Treeptr right;
} Treenode;
