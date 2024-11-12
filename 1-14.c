// Exercise 1-14
// Write a program to print a histogram of the frequencies of different
// characters in its input.

#include <stdio.h>

#define IN  1
#define OUT 0

int main() {
  int c, state, total_chars;
  state = OUT;
  total_chars = 0;
  // 65-91 capital alphabet.
  // 97-122 lowercase alphabet.
  char seen[122];
  for(int i = 65; i < 122; i++)
    seen[i] = 0;

  while((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t'){
      state = OUT; continue;
    }

    seen[c] += 1;
    total_chars += 1;

    if (state == OUT)
      state = IN;
  }

  for(int i = 65; i < 122; i++) {
    if (seen[i] != 0) {
      float freq = (float)seen[i] / (float)total_chars;
      freq *= 100;
      /* printf("%c: %d - %.2f%\n", i, seen[i], freq); */
      printf("%c: ", i);
      for(int j = 0; j < (int)freq; j++)
        printf("|");
      printf("\n%.2f%%\n", freq);
    }
  }
}
