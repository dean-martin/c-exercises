// Exercise 2-8. 
// Write a function rightrot(x,n) that returns the value of the integer x
// rotated to the right by n bit positions.
#include <stdio.h>
#include <limits.h>
#include <math.h>

unsigned rightrot(unsigned x, int n);
unsigned invert(unsigned x, int p, int n);
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned uint_bits();
void binprintf(int v);
int bitcount(unsigned x);

int main()
{
    unsigned x = 21;
    binprintf(x);

    x = rightrot(x, 3);
    binprintf(x);

    x = rightrot(x, 3);
    binprintf(x);

    printf("bitcount of %i: %i\n", x, bitcount(x));
    
    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    unsigned righthalf = getbits(x, n-1, n);

    x = x >> n;

    righthalf = righthalf << bitcount(UINT_MAX) - n;

    return righthalf | x;
}

// A much more concise & logical function from the book than the crap I wrote.
// did not realize the beauty of 01 representing a single bit.
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}

// could've hard coded it since it's just on my machine... doh
// not sure if sizeof would have been useful here instead, haven't taught in book yet.
unsigned uint_bits()
{
    unsigned max = UINT_MAX << 1;
    int len = 0;
    while (max != 0) {
        max = max >> 1;
        len++;
    }
    return len;
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

