#include <assert.h>
#include <stdio.h>

#include "parse.h"
#include "scan.h"
#include "thicc.h"

extern thicc compiler;
static Parser* parser;

// lalr(1)
void thicc_parse_tokens() {
    parser = compiler.parser;
    assert(parser);

    AstNode node;
}
