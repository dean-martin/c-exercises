#include <stdio.h>


int main()
{
    FILE *fp;

    // rwa(b) : read, write, append, binary (for binary files)
    fp = fopen("1.01.c", "r");
    if (fp == NULL) {
        printf("failed to open file\n");
        return -1;
    }

}
