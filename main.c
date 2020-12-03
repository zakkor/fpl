#include <stdio.h>

#include "lexer.h"

int main(void) {
	vec_token tokens = lex("assignment.fpl");
	for (int i = 0; i < tokens.length; i++) {
		struct token t = tokens.data[i];
		printf("Token{ .kind = '%s', .text = '%s', .line = %lu, .col_start = %lu, .col_end = %lu }\n",
			t.kind, t.text, t.line, t.col_start, t.col_end);
	}
	return 0;
}