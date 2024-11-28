// Exercise 1-17
// Write a program to print all input lines that are longer than 80 characters.

#include <stdio.h>
#define MAXLINE 1000 // maximum input line
#define MAX_BUFFER 5000
#define SAVE_WITH_SIZE 80

// getline is defined by stdio (now?), so I have to use an underscore lol.
int _getline(char line[], int maxline);
void copy(char to[], char from[]);
int get_end(char s[]);
void append(char to[], char from[]);

int main() {
  int len; // current line length
  char line[MAXLINE]; // current input line
  char buffer[MAX_BUFFER];

  while ((len = _getline(line, MAXLINE)) > 0) {
    if (len > SAVE_WITH_SIZE) {
      // copy to buffer
      append(buffer, line);
    }
  }

  printf("%s", buffer);

  return 0;
} 

// _getline: read a line into s, return length
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

// copy: copy `from` into `to`; assume to is big enough
void copy(char to[], char from[]) {
  int i;

  i = 0;
  while((to[i] = from[i]) != '\0')
    i++;
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

int get_end(char s[]) {
  int end = 0;
  while(s[end] != '\0')
    end++;

  return end;
}
