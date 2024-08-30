#ifndef THICC_H
#define THICC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "scan.h"
#include "parse.h"

typedef enum {
    INFILE     = 1,
    OUTFILE    = 2,
} CompFlags;

typedef struct {
    FILE*      buffer;
    char*      buffname; 
    Tokenizer* tokenizer;
    Parser*    parser;

    SymbolPos  pos;
  
    CompFlags  flags;
    FILE*      outfile;
    char*      outname;
} thicc;

extern thicc compiler;

void argparse(int argc, char** argv);

#endif
