#include <stdio.h>

#include "lexer.h"

int main(int argc, char** argv) {
	vec_token tokens = lex(argv[1]);
	for (int i = 0; i < tokens.length; i++) {
		struct token t = tokens.data[i];
		printf("Token{ .kind = '%s', .text = '%s', .line = %lu, .col_start = %lu, .col_end = %lu }\n",
			token_kind_str(t.kind), t.text, t.line, t.col_start, t.col_end);
	}
	return 0;
}