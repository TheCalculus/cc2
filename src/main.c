#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "thicc.h"
#include "parse.h"
#include "scan.h"

void argparse(int argc, char** argv, thicc* compiler) {
    char* argname;
    char* argval;

    for (int i = 1; i < argc; i++) {
        argname = argv[i];
        argval = argv[++i];

        if (strcmp(argname, "-o") == 0) {
            compiler->flags |= OUTFILE;
            compiler->outname = argval; 
        }
        else
        if (strcmp(argname, "-s") == 0) {
            // currently source file needs to be appended
            // after this flag, will fix later because this is dumb as fuck
            compiler->flags |= INFILE;
            compiler->buffname = argval;
        }
    }

    // TODO: finish this
    if (compiler->flags & INFILE != INFILE)
        fprintf(stderr, "no source provided with -s\n");
}

thicc* create_compiler() {
    thicc* compiler = (thicc*)malloc(sizeof(thicc));
    assert(compiler);
    compiler->tokenizer = NULL;
    compiler->parser = NULL;
    return compiler;
}

void clean_compiler(thicc* compiler) {
    if (compiler->buffer) fclose(compiler->buffer);
    clean_tokenizer(compiler->tokenizer);
    clean_parser(compiler->parser);
    free(compiler);
    compiler = NULL;
}

int main(int argc, char** argv){
    thicc* compiler = NULL;

    if (argc < 2) {
        fprintf(stderr, "expected argument, received none\n");
        WARN_USAGE();
        return -1;
    }

    compiler = create_compiler();
    argparse(argc, argv, compiler);
    compiler->buffer = fopen(compiler->buffname, "rb");

    if (compiler->buffer == NULL) {
        fprintf(stderr, "source %s does not exist\n", compiler->buffname);
        WARN_USAGE();
        return -1;
    }

    create_tokenizer(compiler->tokenizer);
    thicc_tokenize_source(compiler->tokenizer);
    create_parser(compiler->parser);
    thicc_parse_tokens(compiler->parser);
    fflush(stdout);

    // emit to target or interpret

    WARN_NOT_IMPLEMENTED("code emission");

    if (compiler->flags & INTRPRT == INTRPRT)
    {
        WARN_NOT_IMPLEMENTED("interpret");
        return -1;
    }

    clean_compiler(compiler);
    return 0;
}
