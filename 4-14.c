// Exercise 4-14.
// Define a macro swap(t,x,y) that interchanges two arguments of type t. 
// (Block structure will help.)
#include <stdio.h>

#define dprint(expr)    printf(#expr " = %g\n", expr)
// Using an always true if statement (block structure),
// will keep t tmp in it's own scope. (cool)
#define swap(t,x,y) if (1) { t tmp = x; x = y, y = tmp; }

int main()
{
    float x, y;
    x = 1, y = 2;
    dprint(x/y);

    swap(float, x, y);
    dprint(x/y);
    return 0;
}
