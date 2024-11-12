// Exercise 1-10
// Write a program to copy its input to its output, replacing each tab by \t,
// each backspace by \b, and each backslash by \\. This makes tabs and
// backspaces visible in an unambiguous way.

#include <stdio.h>

char replace_escapes(char c, char escape, char replace) {
  if (c == escape) {
      putchar('\\');
      return replace;
  }

  return c;
}

int main() {
  int c;

  while((c = getchar()) != EOF) {
    c = replace_escapes(c, '\t', 't');
    c = replace_escapes(c, '\b', 'b');
    c = replace_escapes(c, '\\', '\\');

    putchar(c);
  }
}
