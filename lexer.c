#include <stdio.h>
#include <string.h>

#include "lexer.h"

#define LINE_SIZE 512

enum search_kind {
  search_identifier,
  search_number,
  search_nothing,
};

vec_token lex(char *path) {
	FILE* fp = fopen(path, "r");
	vec_token tokens;
	vec_init(&tokens);

	char line[LINE_SIZE];
  enum search_kind searching = search_nothing;
  vec_char_t chunk;
  vec_init(&chunk);
	for (int i = 0; fgets(line, LINE_SIZE, fp); i++) {
    int col_start = -1;

		for (int j = 0; j <= strlen(line); j++) {
			if (line[j] == ' ' || line[j] == '\n') {
				if (searching == search_nothing)
          continue;

        // Add new token with text gathered so far.
        struct token t = {
          .kind = (enum token_kind)searching,
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
        searching = search_nothing;
			} else if (line[j] == '=') {
				struct token t = {
					.kind = token_assignment,
					.text = "=",
          .line = i+1,
          .col_start = col_start,
          .col_end = j+1
				};
				vec_push(&tokens, t);
			} else if (line[j] >= 'a' && line[j] <= 'z') {
        if (searching == search_nothing) {
          searching = search_identifier;
          col_start = j;
        }
				vec_push(&chunk, line[j]);
			} else if (line[j] >= '0' && line[j] <= '9') {
        if (searching == search_nothing) {
          searching = search_number;
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

char* token_kind_str(enum token_kind k) {
  switch (k) {
  case token_identifier:
    return "Identifier";
  case token_number:
    return "Number";
  case token_assignment:
    return "Assignment";
  }
}
