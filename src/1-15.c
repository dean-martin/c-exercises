// Exercise 1-15
// Rewrite the temperature conversion program of Section 1.2 to use a function
// for conversion.

#include <stdio.h>

float fahr_to_celsius(int);

int main() {
  int fahr;

  for (fahr = 300; fahr >= 0; fahr = fahr - 20)
    printf("%3d %6.1f\n", fahr, fahr_to_celsius(fahr));
}

float fahr_to_celsius(int fahr) {
  return (5.0 / 9.0) * (fahr-32);
}
