#include <stdio.h>

#include "lexer.h"

int main(void) {
	vec_token_t tokens = lex("assignment.fpl");
	for (int i = 0; i < tokens.length; i++) {
		printf("Token{ .kind = '%s', .text = '%s' }\n", tokens.data[i].kind, tokens.data[i].text);
	}
	return 0;
}