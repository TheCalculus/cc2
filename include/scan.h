#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef enum {
    UNSIGNED   = 1,
    STATIC     = 2,
    CONST      = 4,
    POINTER    = 8,
    ARRAY      = 16,
    EXTERN     = 32,
    LITERAL    = 64,
} TokenFlags;

typedef enum {
    TOKEN_LITERAL,
    TOKEN_NUMERICAL,
    TOKEN_LROUND,
    TOKEN_RROUND,
    TOKEN_LSQUARE,
    TOKEN_RSQUARE,
    TOKEN_LCURLY,
    TOKEN_RCURLY,
    TOKEN_LTHAN,
    TOKEN_GTHAN,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_FSLASH,
    TOKEN_ASSGN,
    TOKEN_EQUAL,
    TOKEN_NEQUAL,
    TOKEN_EXCLAM,
    TOKEN_AMPERSAND,
    TOKEN_ASTERISK,
    TOKEN_EOF,
} TokenType;

typedef struct {
    char**     filename;
    uint8_t    row;
    uint8_t    col;
} SymbolPos;

typedef struct {
    char       active;
    // token sequence
} Tokenizer;

typedef struct {
    char       value[64];
    SymbolPos  pos;
    TokenType  type;
    TokenFlags flags;
} Token;

void thicc_tokenize_source();

#endif
