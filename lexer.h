#include <stdint.h>

#include "vec.h"

enum token_kind {
  token_identifier,
  token_number,
  token_assignment
};

struct token {
	enum token_kind kind;
	char* text;
  uint32_t line, col_start, col_end;
};

typedef vec_t(struct token) vec_token;

vec_token lex(char *path);

char* token_kind_str(enum token_kind k);
