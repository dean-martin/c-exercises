// Exercise 1-20: detab.
// Write a program _detab_ that replaces tabs in the input with the proper
// number of blanks to space to the next tab stop. Assume a fixed set of tab
// stops, say every _n_ columns. Should _n_ be a variable or a symbolic
// parameter?

#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 4
#define BUFFERSIZE 5000

// These shouldn't be external I'm just fiddling about.
extern char line[];
extern char line_buffer[];
char line[MAXLINE];
char line_buffer[BUFFERSIZE];

void tabstop(char s[]);
void shift(char s[], int start, int amount);
int _getline(char line[], int maxline);
void append(char to[], char from[]);

int main() {
  while(_getline(line, MAXLINE) > 0) {
    tabstop(line);
    append(line_buffer, line);
  }

  printf("%s", line_buffer);

  return 0;
}

void tabstop(char s[]) {
  char c;
  int i;
  for(i = 0; (c = s[i]) != '\0'; i++) {
    if (c == '\t') {
      // I'm too tired to understand why TABSTOP - 1 works but not just TABSTOP.
      // Minus one because we're going to replace the \tab?
      shift(s, i, TABSTOP - 1);
      for(int j = i; j <= i + TABSTOP - 1; j++) {
        s[j] = ' ';
      }
    }
  }
}

int get_end(char s[]) {
  int end = 0;
  while(s[end] != '\0')
    end++;

  return end;
}

void shift(char s[], int start, int amount) {
  char c, swap;
  for (int i = get_end(s); i != start; i--) {
    c = s[i];
    s[i+amount] = c;
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

void append(char to[], char from[]) {
  int append_start = get_end(to);
  to[append_start] = '\n';
  int i = 0;
  while(from[i] != '\0') {
    to[append_start] = from[i];
    ++i;
    ++append_start;
  }
  to[append_start + 1] = '\0';
}
