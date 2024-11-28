// Exercise 4-1.
// Write the function strrindex(s,t), which returns the position of the
// rightmost occurrence of t in s, or -1 if there is none.
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int strrindex(char s[], char t[]);
int _getline(char line[], int max);
int strindex(char source[], char searchFor[]);

char pattern[] = "ould";
char lines[] = 
    "Ah Love! could you and I with Fate conspire\n"
    "To grasp this sorry Scheme of Things entire,\n"
    "Would not we shatter it to bits -- and then\n"
    "Re-mould it nearer to the Heart's Desire!"
;

int main()
{
    char line[MAXLINE];
    int found = 0;
        while (_getline(line, MAXLINE) > 0) {
            int index = strrindex(line, "ou");
            if (index >= 0) {
                printf("index: %i: %s", index, line);
                found++;
            }
        }
    return found;
}

int strrindex(char s[], char t[])
{
    int i, j, k = strlen(t)-1;

    for  (i = strlen(s)-1; i >= 0; i--) {
        for (j=i, k=strlen(t)-1; k >= 0 && s[j]==t[k]; j--, k--) 
            ;
        if (k==-1)
            return i-strlen(t)+1;
    }

    return -1;
}

int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
         for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

int _getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] == '\0';
    return i;
}
