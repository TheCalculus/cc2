#ifndef THICC_H
#define THICC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "scan.h"
#include "parse.h"

typedef enum {
    INFILE  = 1,
    OUTFILE = 2,
} CompFlags;

typedef struct {
    SymbolPos pos;
    CompFlags flags;

    FILE* buffer;
    char* buffname;

    FILE* outfile;
    char* outname;

    Tokenizer* tokenizer;
    Parser* parser;
} thicc;

void argparse(int argc, char** argv);

#endif
