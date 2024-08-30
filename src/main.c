#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thicc.h"
#include "scan.h"

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
    compiler.tokenizer = &(Tokenizer) { 0 };

    if (compiler.buffer == NULL) {
        fprintf(stderr, "source %s does not exist\n", compiler.buffname);
        fprintf(stderr, "usage: thicc -s [source] -o [out]\n");
        return -1;
    }

    thicc_tokenize_source();

    fclose(compiler.buffer);
    return 0;
}
