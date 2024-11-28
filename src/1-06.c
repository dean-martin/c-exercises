// Exercise 1-6
// Verify that the expression getchar() != EOF is 0 or 1.

#include <stdio.h>

int main() {
  int c;
  int t;
  while((t = (c = getchar()) != EOF)) {
    putchar(c);
    printf("EOF: %d\n", t);
  }
  printf("EOF: %d\n", t);
}
