#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vec.h"

#define LINE_SIZE 256

struct token {
	char* kind;
	char* text;
};

void lex(char *path) {
	FILE* fp = fopen(path, "r");
	char buf[LINE_SIZE];
	while (fgets(buf, LINE_SIZE, fp)) {
		int findword = 0;
		vec_char_t word;
		vec_init(&word);
		int findnumber = 0;
		vec_char_t number;
		vec_init(&number);

		for (int i = 0; i <= strlen(buf); i++) {
			if (buf[i] == ' ' || buf[i] == '\n') {
				if (findword) {
					findword = 0;
					printf("IDENT %s\n", word.data);
				} 
				if (findnumber) {
					findnumber = 0;
					printf("NUMBER %s\n", number.data);
				}
			} else if (buf[i] == '=') {
				printf("ASSIGN\n");
			} else if (buf[i] >= 'a' && buf[i] <= 'z') {
				if (!findword) {
					findword = 1;
					vec_clear(&word);
				}
				vec_push(&word, buf[i]);
			} else if (buf[i] >= '0' && buf[i] <= '9') {
				if (!findnumber) {
					findnumber = 1;
					vec_clear(&number);
				}
				vec_push(&number, buf[i]);
			}
		}
	}
	fclose(fp);
}

int main(void) {
	lex("assignment.fpl");
	return 0;
}