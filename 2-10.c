// Exercise 2-10.
// Rewrite the function lower, which converts upper case letters to lower case,
// with a conditional expression instead of if-else.
#include <stdio.h>


int lower(char c);
void test(int c);

int main()
{
    test('a');
    test('A');
    test('B');
    test('Z');
    test('U');
}


int lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

void test(int c)
{
    c = lower(c);
    printf("%c: %i\n", c, c);
}
