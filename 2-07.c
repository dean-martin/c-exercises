// Exercise 2-7. 
// Write a function invert(x,p,n) that returns x with the n bits that begin at
// position p inverted (i.e., 1 changed into 0 and vice verse), leaving the
// others unchanged.
#include <stdio.h>
#include <math.h>

unsigned invert(unsigned x, int p, int n);
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
void binprintf(int v);

int main()
{
    unsigned x = 4;
    binprintf(x);

    x = invert(x, 4, 3);
    binprintf(x);
    
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    unsigned bits = getbits(x, p, n) << p-n+1;
    return setbits(x, p, n, ~bits);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned bits = getbits(y, p ,n) << p-n+1;
    unsigned to_zero = (~(~0 << n)) << p-n+1; // get a mask to zero the bits in the p to n position on x.
    x = x & ~to_zero; // zero out bits in x from the mask (p to n)

    return x | bits; // turn on the bits sliced from y
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}

void binprintf(int v)
{
    unsigned int mask=1<<((sizeof(int)<<3)-1);
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
    printf(": %i\n", v);
}
