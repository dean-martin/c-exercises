// Exercise 1-18
// Write a program to remove trailing blanks and tabs from each line of input,
// and to delete entirely blank lines.

#include <stdio.h>
#define MAXLINE 1000
#define MAX_BUFFER 5000

int _getline(char line[], int maxline);
int get_end(char s[]);
void append(char to[], char from[]);
void trim(char line[]);

int main() {
  char line[MAXLINE];
  char buffer[MAX_BUFFER];

  while(_getline(line, MAXLINE) > 0) {
    /* printf("size: %d\n", get_end(line)); */
    trim(line);
    /* printf("trimed size: %d\n", get_end(line)); */
    if (line[0] != '\0')
      append(buffer, line);
  }

  /* printf("buffersize: %d\n", get_end(buffer)); */
  printf("%s", buffer);
}

int is_space(char c) {
  return c == '\t' || c == ' ';
}

void trim(char line[]) {
  char c, prev;
  int delete_start = -1;
  int end = get_end(line);
  for(int i=0; i != end; i++) {
    c = line[i];
    if (i != 0)
      prev = line[i-1];
    if (is_space(c) && !is_space(prev))
        delete_start = i;
  }

  // Trim the string.
  if (delete_start != -1) {
    line[delete_start] = '\n';
    // Keeping the original \n though.
    line[delete_start+1] = '\0';
  }

  if (line[0] == '\n') {
    line[0] = '\0';
    return;
  }
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
