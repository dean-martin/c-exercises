// Exercise 1-19
// Write a function reverse(s) that reverses the character string s. Use it to
// write a program that revserses its input a line at a time.

#include <stdio.h>
#define MAXLINE 1000

void reverse(char s[]);
int _getline(char[], int);

int main() {
  char line[MAXLINE];
  while(_getline(line, MAXLINE) > 0) {
    reverse(line);
    printf("%s\n", line);
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

int get_end(char s[]) {
  int end = 0;
  while(s[end] != '\0')
    end++;

  return end;
}

void reverse(char s[]) {
  int i, j, max;
  i = 0;
  j = max = get_end(s);
  for(i = 0; i != max/2; i++) {
    j--;
    char tmp = s[j];
    s[j] = s[i];
    s[i] = tmp;
  }
}
