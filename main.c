#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vec.h"

#define LINE_SIZE 256

int readfile(char*** readlines, char* path) {
	FILE* fp = fopen(path, "r");
	char** lines = malloc(1 * sizeof(char*));
	for (int i = 0; ; i++) {
		lines[i] = malloc(LINE_SIZE);
		if (!fgets(lines[i], LINE_SIZE, fp)) {
			fclose(fp);
			*readlines = lines;
			return i;
		}
		lines = realloc(lines, (i+2) * sizeof(char*));
	}
}

struct token {
	char* type;
	char* data;
};

void lex(char *path) {
	FILE* fp = fopen(path, "r");
	char buf[LINE_SIZE];
	while (fgets(buf, LINE_SIZE, fp)) {
		vec_char_t word;
		vec_init(&word);

		for (int i = 0; i < strlen(buf); i++) {
			if (buf[i] == ' ') {
				printf("IDENT %s\n", word.data);
			} else if (buf[i] == '=') {
				printf("ASSIGN\n");
			} else if (buf[i] >= 'a' && buf[i] <= 'z') {
				vec_push(&word, buf[i]);
			} else if (buf[i] >= '0' && buf[i] <= '9') {
				printf("DIGIT\n");
			}
		}
	}
	fclose(fp);
}

int main(void) {
	lex("assignment.fpl");
	return 0;
}