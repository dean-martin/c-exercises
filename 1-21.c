// Exercise 1-21: entab.
// Write a program entab that replaces strings of blanks by the minimum number
// of tabs and blanks to achieve the same spacing. Use the same tab stops as for
// detab. When either a tab or a single blank would suffice to reach a tab stop,
// which should be given preference?

#include <stdio.h>
#define MAXLINE 1000
#define TABSTOP 4

void entab(char s[]);
void slice(char s[], int start, int stop);
int _getline(char line[], int maxline);

int main() {
  char line[MAXLINE];
  while(_getline(line, MAXLINE) > 0) {
    entab(line);
    printf("%s", line);
  }

  return 0;
}

void entab(char s[]) {
  int i, blank_start = 0, blank_count = 0;
  char c, prev;
  for(i = 0; (c = s[i]) != '\0'; i++) {
    if (c == ' ') {
      blank_count++; 
      if (prev != ' ')
        blank_start = i;
    } 
    else 
      blank_count = 0;

    if (blank_count == TABSTOP) {
      slice(s, blank_start, i);
      s[blank_start] = '\t';
      blank_count = 0;
      i = blank_start;
      prev = s[i];
      // I originally wanted to do this with recursion, but technically I
      // haven't been taught it from the book, and it's much more inefficient
      // unless I give it a starting index.
      /* return entab(s); */
    }
    else
      prev = c;
  }
}

void slice(char s[], int start, int end) {
  char c;
  int i = start;
  int shift = end - start;
  for(; (c = s[i]) != '\0'; i++) {
    s[i] = s[i + shift];
  }
}

int _getline(char s[], int lim) {
  int c, i;

  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}
