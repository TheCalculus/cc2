#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thicc.h"
#include "error.h"
#include "parse.h"
#include "scan.h"

#define WARN_USAGE()               fprintf(stderr, "usage: thicc -s [source] -o [out]\n");
#define WARN_NOT_IMPLEMENTED(msg)  fprintf(stderr, "WARN: " msg " not yet implemented\n");

// main compiler process
// compiler process can be extern'd
thicc compiler;

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
    if (compiler.flags & INFILE != INFILE)
        fprintf(stderr, "no source provided with -s\n");
}

int main(int argc, char** argv){
    compiler = (thicc) { 0 };

    if (argc < 2) {
        fprintf(stderr, "expected argument, received none\n");
        WARN_USAGE();
        return -1;
    }

    argparse(argc, argv);

    compiler.buffer = fopen(compiler.buffname, "rb");

    if (compiler.buffer == NULL) {
        fprintf(stderr, "source %s does not exist\n", compiler.buffname);
        WARN_USAGE();
        return -1;
    }

    #define INIT_VECTOR_SIZE 16
    assert(INIT_VECTOR_SIZE > 0);

    Tokenizer tokenizer = {
        .flags = FROM_FILE | DEBUG,
        .tokens = new_vector(sizeof(Token) * INIT_VECTOR_SIZE),
        .buffer = { 0 },
    };

    tokenizer.active = (char*)tokenizer.buffer;
    
    thicc_tokenize_source(&tokenizer);

    Parser parser = { .ast = new_vector(sizeof(AstNode) * INIT_VECTOR_SIZE) };
    // token vector will never be NULL
    thicc_parse_tokens(&parser);

    fflush(stdout);

    // emit to target or interpret

    WARN_NOT_IMPLEMENTED("code emission");

    if (compiler.flags & INTRPRT == INTRPRT)
    {
        WARN_NOT_IMPLEMENTED("interpret");
        return -1;
    }

    free_vector(tokenizer.tokens);
    free_vector(parser.ast);

    fclose(compiler.buffer);
    return 0;
}
