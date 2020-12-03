#include <stdint.h>

#include "vec.h"

struct token {
	char* kind;
	char* text;
  uint32_t line, col_start, col_end;
};

typedef vec_t(struct token) vec_token;

vec_token lex(char *path);