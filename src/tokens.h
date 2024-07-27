#ifndef COMPILER_H
#define COMPILER_H

#include <stdint.h>
#include <stdio.h>

typedef enum {
    TOKEN_LITERAL,
    TOKEN_NUMERICAL,
    TOKEN_LROUND,
    TOKEN_RROUND,
    TOKEN_LSQUARE,
    TOKEN_RSQUARE,
    TOKEN_LCURLY,
    TOKEN_RCURLY,
    TOKEN_SEMICOLON,
    TOKEN_AMPERSAND,
    TOKEN_ASTERISK,
    TOKEN_EOF,
} TokenType;

typedef struct {
    char      value[64];
    uint8_t   row;
    uint8_t   col;
    TokenType type;
} Token;

typedef struct {
    FILE*   buffer;
    char*   buffname;
    uint8_t row;
    uint8_t col;
    char    active;
} Tokenizer;

#endif
