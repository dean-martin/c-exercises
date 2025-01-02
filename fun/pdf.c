#include <stdio.h>
#include <ctype.h>

int main()
{
    printf("hello, world!\n");
    int c;
    unsigned int i = 0;
    while ((c = getchar()) != EOF) {
        if (c != 033) // ignore clear screen
            printf("%c", c);
        if (i++ > 500000)
            break;
    }
    return 0;
}
