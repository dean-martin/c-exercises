// Exercise 2-9.
// In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
// in x. Explain why. Use this observation to write a faster version of
// bitcount.
#include <stdio.h>
#include <limits.h>

int bitcountfast(unsigned x);
int bitcount(unsigned x);
void binprintf(int v);

int main()
{
    printf("hello, world\n");

    unsigned x = 15;
    for (int i = 56; i >= 31; i--) {
        binprintf(i);
    }
    // & bitwise AND is often used to mask off some set bf bits;
    // n = n & 0177;
    // sets to zero all but the low-order 7 bits of n.

    // There are two cases to observe in x &= x - 1.
    // Starting with the easier case, as we subtract 1, the least significant
    // bit will be alternating on and off.
    // e.g.
    // 110111 55 
    // 110110 54
    // 110101 53
    // on, off, on

    // When applying the AND operator, if x LSB is 1, and x-1 LSB is 0, 
    // then since is 0 in x-1, that bit will be masked off.
    
    // The second case is harder...

    // as we step up the power of twos, the leading zeros start to back fill, left to right,
    // from the current power of two.
    // 110111 55 
    // 110110 54
    // 110101 53 1^1 shifted to 1^0
    // 110100 52 // 1^0 fell off the end
    // 110011 51 // next power
    // 110010 50 // odd number
    // 110001 49 // next power

    // When we step off to the next power, the bits to the right of that power will be on.
    // A climbing up effect maybe...
    // I'm sure there's some viral video showing this with cool animations.
    // Doing it yourself is better, of course!

    x = 14;
    printf("%i\n", bitcountfast(UINT_MAX));
}

int bitcountfast(unsigned x)
{
    int n;
    for (n = 0; x != 0; n++)
        x &= x-1;

    return n;
}

int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
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


