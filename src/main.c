#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "scan.h"
#include "thicc.h"

thicc compiler = { 0 };

void argparse(int argc, char** argv) {
    char* argname;
    char* argval;

    for (int i = 1; i < argc; i++) {
        argname = argv[i];
        argval = argv[++i];

        if (strcmp(argname, "-o") == 0) {
            compiler.flags |= OUTFILE;
            compiler.outname = argval; 
        }
        else
        if (strcmp(argname, "-s") == 0) {
            // currently source file needs to be appended
            // after this flag, will fix later because this is dumb as fuck
            compiler.flags |= INFILE;
            compiler.buffname = argval;
        }
    }

    // TODO: finish this
    if (compiler.flags & INFILE == 0)
        fprintf(stderr, "no source provided with -s\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "expected argument, received none\n");
        fprintf(stderr, "usage: thicc -s [source] -o [out]\n");
        return -1;
    }

    argparse(argc, argv);

    compiler.buffer = fopen(compiler.buffname, "rb");

    if (compiler.buffer == NULL) {
        fprintf(stderr, "source %s does not exist\n", compiler.buffname);
        fprintf(stderr, "usage: thicc -s [source] -o [out]\n");
        return -1;
    }

    Tokenizer scanner = { .tokens = new_vector(sizeof(Token) * 10) };
    compiler.tokenizer = &scanner;

    assert(compiler.tokenizer->tokens.data);

    thicc_tokenize_source();

    Parser parser = { .ast = new_vector(sizeof(AstNode) * 10) };
    compiler.parser = &parser;

    // check whether token vector is defined
    if (compiler.tokenizer->tokens.data != NULL)
        thicc_parse_tokens();

    free_vector(&compiler.tokenizer->tokens);
    free_vector(&compiler.parser->ast);

    fclose(compiler.buffer);
    return 0;
}
