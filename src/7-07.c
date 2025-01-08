// Exercise 7-6.
// Write a program to compare two files, printing the first line
// where they differ.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    if (--argc != 2) {
        fprintf(stderr, "usage: %s file1 file2\n", argv[0]);
        return 1;
    }
    FILE *one = NULL;
    FILE *two = NULL;

    if ((one = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "failed to open file '%s'\n", argv[1]);
        exit(1);
    }
    if ((two = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "failed to open file '%s'\n", argv[2]);
        exit(1);
    }

    char sone[MAXLINE];
    char stwo[MAXLINE];

    int i = -1;
    do {
        if (fgets(sone, MAXLINE, one) == NULL)
            break;
        if (fgets(stwo, MAXLINE, two) == NULL)
            break;
        i++;
    } while (strcmp(sone, stwo) == 0);

    if (strcmp(sone, stwo) != 0) {
        printf("line: %d\n", i);
        printf("%12s: %s", argv[1], sone);
        printf("%12s: %s", argv[2], stwo);
        return 1;
    }

    return 0;
}
