#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"
#include "tokens.h"

bool is_invalid(char ch) {
    return isspace(ch);
}

void advance_buffer(Tokenizer* tokenizer) {
    tokenizer->active = getc(tokenizer->buffer);
}

void advance_characters(Tokenizer* tokenizer) {
    do {
        advance_buffer(tokenizer);
    } while (is_invalid(tokenizer->active));
}

void read_literal(Tokenizer* tokenizer, Token* token) {
    size_t i = 0;

    do {
        token->value[i++] = tokenizer->active;
        advance_buffer(tokenizer);
    } while (!is_invalid(tokenizer->active));

    token->value[i] = '\0';
}

Token next_token(Tokenizer* tokenizer) {
    Token token = { 0 };
    advance_characters(tokenizer);

    switch (tokenizer->active) {
        case EOF:
            token.type = TOKEN_EOF;
            break;

        default:
            read_literal(tokenizer, &token);
            token.type = TOKEN_LITERAL;
            printf("%s\n", token.value);
    }

    return token;
}

int main() {
    Tokenizer tokenizer = { 0 };
    tokenizer.buffer = fopen("test.c", "rb");

    while (next_token(&tokenizer).type != TOKEN_EOF)
        ;

    fclose(tokenizer.buffer);
    return 0;
}
