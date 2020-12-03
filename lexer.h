#include "vec.h"

struct token {
	char* kind;
	char* text;
};

typedef vec_t(struct token) vec_token_t;

vec_token_t lex(char *path);