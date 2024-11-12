// Exercise 2-6. 
// Write a function setbits(x,p,n,y) that returns x with the n bits that begin
// at position p set to the rightmost n bits of y, leaving the other bits
// unchanged.
#include <stdio.h>
#include <math.h>

unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
void binprintf(int v);

int main()
{
    unsigned x = 6;
    unsigned y = 25;
    binprintf(x);
    binprintf(y);

    x = setbits(x, 4, 3, y);
    binprintf(x);

    x = 0;
    y = ~0;
    binprintf(x);
    binprintf(y);

    x = setbits(x, 10, 4, y);
    binprintf(x);
    
    return 0;
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
