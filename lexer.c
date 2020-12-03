#include <stdio.h>
#include <string.h>

#include "lexer.h"

#define LINE_SIZE 512

enum search_kind {
  nothing,
  word,
  number
};

vec_token lex(char *path) {
	FILE* fp = fopen(path, "r");
	vec_token tokens;
	vec_init(&tokens);

	char line[LINE_SIZE];
  enum search_kind searching = nothing;
  vec_char_t chunk;
  vec_init(&chunk);
	for (int i = 0; fgets(line, LINE_SIZE, fp); i++) {
    int col_start = -1;

		for (int j = 0; j <= strlen(line); j++) {
			if (line[j] == ' ' || line[j] == '\n') {
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
          .text = malloc(strlen(chunk.data)+1),
          .line = i+1,
          .col_start = col_start,
          .col_end = j+1
        };
        strncpy(t.text, chunk.data, strlen(chunk.data)+1);
        vec_push(&tokens, t);

        // Reset search.
        vec_clear(&chunk);
        vec_compact(&chunk);
        searching = nothing;
			} else if (line[j] == '=') {
				struct token t = {
					.kind = "Assign",
					.text = "=",
          .line = i+1,
          .col_start = col_start,
          .col_end = j+1
				};
				vec_push(&tokens, t);
			} else if (line[j] >= 'a' && line[j] <= 'z') {
        if (searching == nothing) {
          searching = word;
          col_start = j;
        }
				vec_push(&chunk, line[j]);
			} else if (line[j] >= '0' && line[j] <= '9') {
        if (searching == nothing) {
          searching = number;
          col_start = j;
        }
        col_start = j;
				vec_push(&chunk, line[j]);
			}
		}
	}
	fclose(fp);

	return tokens;
}