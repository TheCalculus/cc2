#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "general.h"
#include "scan.h"
#include "thicc.h"

static Token next_token(Tokenizer* tokenizer);
static inline void advance_buffer(Tokenizer* tokenizer);
static void advance_characters(Tokenizer* tokenizer);
static void read_identifier(Tokenizer* tokenizer, Token* token);
static void read_literal(Token* token);

Tokenizer* create_tokenizer() {
    Tokenizer* tokenizer = (Tokenizer*)malloc(sizeof(Tokenizer));
    assert(tokenizer);
    tokenizer->flags = FROM_FILE | DEBUG;
    tokenizer->tokens = new_vector(sizeof(Token) * INIT_VECTOR_SIZE);
    return tokenizer;
}

void clean_tokenizer(Tokenizer* tokenizer) {
    if (tokenizer == NULL) return;
    free_vector(tokenizer->tokens);
    free(tokenizer);
    tokenizer = NULL;
}

static inline void advance_buffer(Tokenizer* tokenizer) {
    tokenizer->active++;
    // compiler.pos.row++;
}

static void advance_characters(Tokenizer* tokenizer) {
    while (isspace(tokenizer->active))
        advance_buffer(tokenizer);
}

static void read_identifier(Tokenizer* tokenizer, Token* token) {
    size_t i = 0;

    while (isalpha(tokenizer->active)) {
        token->value[i++] = tokenizer->active;
        advance_buffer(tokenizer);
    }

    token->value[i] = '\0';
}

static Token next_token(Tokenizer* tokenizer) {
    Token token = { 0 };

    advance_characters(tokenizer);

    token.value[0] = tokenizer->active;
    token.value[1] = 0;

    switch (tokenizer->active) {
        case '(':
            token.type = TOKEN_LROUND;
            break;
        case ')':
            token.type = TOKEN_RROUND;
            break;
        case '[':
            token.type = TOKEN_LSQUARE;
            break;
        case ']':
            token.type = TOKEN_RSQUARE;
            break;
        case '<':
            token.type = TOKEN_LTHAN;
            break;
        case '>':
            token.type = TOKEN_GTHAN;
            break;
        case '{':
            token.type = TOKEN_LCURLY;
            break;
        case '}':
            token.type = TOKEN_RCURLY;
            break;
        case ';':
            token.type = TOKEN_SEMICOLON;
            break;
        case ',':
            token.type = TOKEN_COMMA;
            break;
        case '+':
            token.type = TOKEN_PLUS;
            break;
        case '-':
            token.type = TOKEN_MINUS;
            break;
        case '=':
            token.type = TOKEN_ASSGN;
            break;
        case '!':
            token.type = TOKEN_EXCLAM;
            break;
        case '/':
            token.type = TOKEN_FSLASH;
            break;
        case '&':
            token.type = TOKEN_AMPERSAND;
            break;
        case '*':
            token.type = TOKEN_ASTERISK;
            break;

        case EOF:
            token.type = TOKEN_EOF;
            token.value[0] = 0;
            break;

        default:
            if (!isalpha(tokenizer->active)) break;

            token.type = TOKEN_LITERAL;
            read_identifier(tokenizer, &token);

            return token;
    }

    advance_buffer(tokenizer);

    return token;
}

#define DEBUG

void thicc_tokenize_source(thicc* compiler) {
    Tokenizer* tokenizer = compiler->tokenizer;
    assert(tokenizer);

    // assume FROM_FILE
    while (!feof(compiler->buffer)) {
        size_t nread = fread(tokenizer->buffer, sizeof(*tokenizer->buffer), TOKENIZER_BUFFER_LENGTH, compiler->buffer);
        assert(nread > 0);
        tokenizer->active = (char*)tokenizer->buffer;

        Token token;
        for (size_t i = 0; i < nread; i++) {
            if (tokenizer->active == '\0') return;
            token = next_token(tokenizer);
            push_vector(tokenizer->tokens, &token);
#ifdef DEBUG
            printf("%s", token.value);
#endif
        }
    }
}
