// Exercise 2-1
// Write a program to determine the ranges of char, short, int, and long
// variables, both signed and unsigned, by printing appropriate values from
// standard headers and by direct computation. Harder if you compute them:
// determine the ranges of the various floating-point types.

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
  printf("CHAR_BIT: %d\n", CHAR_BIT);
  printf("CHAR_MAX: %d\n", CHAR_MAX);
  printf("CHAR_MIN: %d\n\n", CHAR_MIN);

  printf("INT_MAX: %d\n", INT_MAX);
  printf("INT_MIN: %d\n\n", INT_MIN);

  printf("LONG_MAX: %li\n", LONG_MAX);
  printf("LONG_MIN: %li\n\n", LONG_MIN);

  printf("SCHAR_MAX: %i\n", SCHAR_MAX);
  printf("SCHAR_MIN: %i\n\n", SCHAR_MIN);

  printf("SHRT_MAX: %i\n", SHRT_MAX);
  printf("SHRT_MIN: %i\n\n", SHRT_MIN);

  printf("UCHAR_MAX: %d\n\n", UCHAR_MAX);

  printf("UINT_MAX: %i\n\n", UINT_MAX);

  printf("ULONG_MAX: %li\n\n", ULONG_MAX);

  printf("USHRT_MAX: %i\n\n", USHRT_MAX);

  // Floats
  printf("FLT_RADIX: %d\n\n", FLT_RADIX);
  printf("FLT_ROUNDS: %d\n\n", FLT_ROUNDS);
  printf("FLT_DIG: %d\n\n", FLT_DIG); // decimal digits of precision
}
