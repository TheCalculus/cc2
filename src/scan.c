#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "thicc.h"
#include "scan.h"

// forwards
static Token next_token         (Tokenizer* tokenizer);
static bool  is_whitespace      (char ch);
static bool  is_invalid         (char ch);
static void  advance_buffer     ();
static void  advance_characters (Tokenizer* tokenizer);
static void  read_literal       (Tokenizer* tokenizer, Token* token);

static bool
is_invalid(char ch) {
    return isspace(ch);
}

static void
advance_buffer() {
    compiler.tokenizer->active = getc(compiler.buffer);
    compiler.pos.row++;
}

static void
skip_whitespace(Tokenizer* tokenizer) {
    while (isspace(tokenizer->active))
        advance_buffer();
}

static void
advance_characters(Tokenizer* tokenizer) {
    do { advance_buffer(tokenizer); }
    while (is_invalid(tokenizer->active));
}

static void
read_identifier(Tokenizer* tokenizer, Token* token) {
    size_t i = 0;

    while (isalpha(tokenizer->active)) {
        token->value[i++] = tokenizer->active;
        advance_buffer(tokenizer);
    }

    token->value[i] = '\0';
}

static Token
next_token(Tokenizer* tokenizer) {
    Token token = { 0 };

    skip_whitespace(tokenizer);

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

void thicc_tokenize_source() {
    Token token;

    while ((token = next_token(compiler.tokenizer))
            .type != TOKEN_EOF)
        printf("%s", token.value);
}
