// Exercise 1-13
// Write a program to print a histogram of the lengths of words in its input. It
// is easy to draw the histogram with the bars horizontal; a vertical
// orientation is more challenging.

#define MAX_WORD_SIZE 20
#define IN  1
#define OUT 2

#include <stdio.h>

int main() {
  int c, char_index;
  int state = OUT;
  char_index = 0;

  int words[MAX_WORD_SIZE];
  for(int i = 0; i < MAX_WORD_SIZE; i++)
    words[i] = 0;

  while((c = getchar()) != EOF) {
    // Current word finished, next.
    if (c == ' ' || c == '\n' || c == '\t') {
      state = OUT;
      words[char_index] += 1;
      char_index = 0;
      continue;
    } 
    char_index++;
    if (state == OUT)
      state = IN;
  }

  for(int i = 0; i < MAX_WORD_SIZE; i++) {
    if (i < 10)
      printf(" %d:", i);
    else
      printf("%d: ", i);
    for (int j = 0; j < words[i]; j++)
      printf("|");
    printf("\n");
  }
}
