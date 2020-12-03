#include <stdio.h>
#include <string.h>

#include "lexer.h"

#define LINE_SIZE 256

vec_token_t lex(char *path) {
	FILE* fp = fopen(path, "r");
	vec_token_t tokens;
	vec_init(&tokens);

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
					struct token t = {
						.kind = "Identifier",
            // TODO: Need to free this:
            .text = malloc(strlen(word.data))
					};
          strncpy(t.text, word.data, strlen(word.data));
					vec_push(&tokens, t);
				} 
				if (findnumber) {
					findnumber = 0;
					struct token t = {
						.kind = "Number",
            // TODO: Need to free this:
						.text = malloc(strlen(number.data))
					};
          strncpy(t.text, number.data, strlen(number.data));
					vec_push(&tokens, t);
				}
			} else if (buf[i] == '=') {
				struct token t = {
					.kind = "Assign",
					.text = "="
				};
				vec_push(&tokens, t);
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

	return tokens;
}