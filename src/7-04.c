// Exercise 7-04
// Write a private version of scanf analogous to minprintf from
// the previous section.
#include <stdio.h>

#define printsize(thing) printf(#thing " = %d\n", sizeof(thing));
/*
#define dprint(expr)    printf(#expr " = %g\n", expr)
#define swap(t,x,y) if (1) { t tmp = x; x = y, y = tmp; }
*/

int main()
{
    double sum, v;

    sum = 0;
    while (scanf("%lf", &v) == 1)
        printf("\t%.2f\n", sum += v);

    return 0;
}
