#include <stdio.h>
#include <string.h>

#include "lexer.h"

#define LINE_SIZE 256

enum search_kind {
  nothing,
  word,
  number
};

vec_token_t lex(char *path) {
	FILE* fp = fopen(path, "r");
	vec_token_t tokens;
	vec_init(&tokens);

	char buf[LINE_SIZE];
	while (fgets(buf, LINE_SIZE, fp)) {
    enum search_kind searching = nothing;
    vec_char_t chunk;
		vec_init(&chunk);

		for (int i = 0; i <= strlen(buf); i++) {
			if (buf[i] == ' ' || buf[i] == '\n') {
        int add = 0;
        char *kind;
				if (searching == word) {
          add = 1;
          kind = "Identifier";
				} else if (searching == number) {
          add = 1;
          kind = "Number";
				}
        if (!add) {
          continue;
        }

        // Add new token with text gathered so far.
        struct token t = {
          .kind = kind,
          // TODO: Need to free this:
          .text = malloc(strlen(chunk.data))
        };
        strncpy(t.text, chunk.data, strlen(chunk.data));
        vec_push(&tokens, t);

        // Reset search.
        vec_clear(&chunk);
        searching = nothing;
			} else if (buf[i] == '=') {
				struct token t = {
					.kind = "Assign",
					.text = "="
				};
				vec_push(&tokens, t);
			} else if (buf[i] >= 'a' && buf[i] <= 'z') {
        searching = word;
				vec_push(&chunk, buf[i]);
			} else if (buf[i] >= '0' && buf[i] <= '9') {
        searching = number;
				vec_push(&chunk, buf[i]);
			}
		}
	}
	fclose(fp);

	return tokens;
}