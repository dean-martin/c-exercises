// Exercise 1-9
// Write a program to copy its input to its output, replacing each string of one
// or more blanks by a single blank.

#include <stdio.h>

int main() {
  int c, prev;

  while((c = getchar()) != EOF) {
    // I'm trying to program this as if I don't know what && and
    // continue syntax is. As to follow along with what the book has
    // taught so far.
    if (c != ' ')
      putchar(c);

    if (c == ' ')
      if (prev != ' ')
        putchar(c);

    prev = c;
  }
}
