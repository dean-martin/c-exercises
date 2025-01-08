#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("usage: pdftext filename.pdf\n");
        return -1;
    }

    FILE *fp = NULL;
    if ((fp = fopen(argv[1], "rb")) == NULL) {
        printf("failed top open file '%s'\n", argv[1]);
        return -1;
    }
    int c;
    unsigned int i = 0;
    while ((c = getc(fp)) != EOF) {
        if (c != 033) // ignore clear screen
            putc(c, stdout);
        if (i++ > 500000)
            break;
    }
    putc('\n', stdout);
    return 0;
}
