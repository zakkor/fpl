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

        // TODO: Need to free this:
        char* text = malloc(strlen(chunk.data)+1);
        strncpy(text, chunk.data, strlen(chunk.data)+1);
        // Add new token with text gathered so far.
        token_add(&tokens, (enum token_kind)searching, text, i+1, col_start, j+2);

        // Reset search.
        vec_clear(&chunk);
        vec_compact(&chunk);
        searching = search_nothing;
			} else if (line[j] == '{') {
        token_add_singlechar(&tokens, token_leftbrace, "{", i+1, j+1);
      } else if (line[j] == '}') {
        token_add_singlechar(&tokens, token_rightbrace, "}", i+1, j+1);
      } else if (line[j] == '=') {
        token_add_singlechar(&tokens, token_assignment, "=", i+1, j+1);
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


void token_add(vec_token* vec, enum token_kind kind, char* text, int line, int col_start, int col_end) {
  struct token t = {
    .kind = kind,
    .text = text,
    .line = line,
    .col_start = col_start,
    .col_end = col_end
  };
  vec_push(vec, t);
}

void token_add_singlechar(vec_token* vec, enum token_kind kind, char* text, int line, int col) {
  struct token t = {
    .kind = kind,
    .text = text,
    .line = line,
    .col_start = col,
    .col_end = col+1
  };
  vec_push(vec, t);
}

char* token_kind_str(enum token_kind k) {
  switch (k) {
  case token_identifier:
    return "Identifier";
  case token_number:
    return "Number";
  case token_assignment:
    return "Assignment";
  case token_leftbrace:
    return "LeftBrace";
  case token_rightbrace:
    return "RightBrace";
  }
}
