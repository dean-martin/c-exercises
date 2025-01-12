#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("usage: pdftext filename.pdf\n");
		return -1;
	}

	FILE *fp = NULL;
	if ((fp = fopen(argv[1], "rb")) == NULL) {
		printf("failed top open file '%s'\n", argv[1]);
		return -1;
	}

	char *text = (char *) malloc(sizeof(char[10000]));

	int c = 0, prev = 0;
#define TEXTBLOCK 1
#define TEXT 2
	unsigned long state = 0;

	for (; (c = getc(fp)) != EOF; prev = c) {
		if (prev == 'B' && c == 'T') {
			state |= TEXTBLOCK;
			continue;
		}
		if ((state & TEXTBLOCK) && prev == 'E' && c == 'T') {
			state &= ~TEXTBLOCK;
			printf("WE OUTTA HERE\n");
			return 0;
			continue;
		}

		if (c == '(') {
			state |= TEXT;
		}
		if (state & TEXT) {
			if (c == ')') {
				state &= ~TEXT;
				printf("off\n");
				continue;
			}
			if (strlen(text) > 500)
				break;
			if (isalpha(c) || isspace(c)) {
				printf("%c", c);
				*text++ = c;
			}
		}
	}

	*text = '\0';

	printf("strlen(text) == %ld\ntext: %s", strlen(text), text);

	return 0;
}

