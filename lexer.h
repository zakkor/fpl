#include <stdint.h>

#include "vec.h"

enum token_kind {
	token_identifier,
	token_number,
	token_assignment,
	token_leftbrace,
	token_rightbrace
};

struct token {
	enum token_kind kind;
	char* text;
	uint32_t line, col_start, col_end;
};

typedef vec_t(struct token) vec_token;

void token_add(vec_token* vec, enum token_kind kind, char* text, int line, int col_start, int col_end);

void token_add_singlechar(vec_token* vec, enum token_kind kind, char* text, int line, int col);

vec_token lex(char *path);

char* token_kind_str(enum token_kind k);
