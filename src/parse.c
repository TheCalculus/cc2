#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "scan.h"
#include "thicc.h"

extern thicc compiler;
static Parser* parser;

Parser* create_parser() {
    Parser* parser = (Parser*)malloc(sizeof(parser));
    assert(parser);
    parser->ast = new_vector(sizeof(AstNode) * INIT_VECTOR_SIZE);
    return parser;
}

void clean_parser(Parser* parser) {
    if (parser == NULL) return;
    free_vector(parser->ast);
    free(parser);
    parser = NULL;
}

// lalr(1)
void thicc_parse_tokens(Parser* parser) {
    assert(parser);
    AstNode node;
}
