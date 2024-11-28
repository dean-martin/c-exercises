// Exercise 3-2.
// Write a function escape(s,t) that converts characters like newline and tab
// into visible escape sequences like \n and \t as it copies the string t to s.
// Use a switch. Write a function for the other direction as well, converting
// escape sequences into the real characters. 
#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
    char s[] = "hello,\tworld\n\n";
    char t[100];
    escape(s, t);
    printf("%s", s);
    printf("%s", t);

    char ut[100];
    unescape(t, ut);
    printf("\n");
    printf("%s", ut);
}

void escape(char s[], char t[])
{
    char c;
    char ti = 0;
    for (int i = 0; (c = s[i]) != '\0'; i++) {
        switch (c) {
            case '\n':
            case '\t':
                t[ti++] = '\\';
                t[ti++] = (c == '\n') ? 'n' : 't';
                break;
            default: 
                t[ti++] = c;
            break;
        }
    }
}

void unescape(char s[], char t[])
{
    char c, prev;
    char ti = 0;
    // oooo comma operators
    for (int i = 0; prev = c, (c = s[i]) != '\0'; i++) {
        switch (c) {
            case 'n':
            case 't':
                if (prev == '\\') {
                    t[ti-1] = (c == 'n') ? '\n' : '\t';
                }
                break;
            default: 
                t[ti++] = c;
                break;
        }
    }
}
