#ifndef COMPILER_H
#define COMPILER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "tokenizer.h"

typedef enum {
    INFILE     = 1,
    OUTFILE    = 2,
} CompFlags;

typedef struct {
    FILE*      buffer;
    char*      buffname; 
    Tokenizer* tokenizer;
    SymbolPos  pos;
  
    CompFlags  flags;
    FILE*      outfile;
    char*      outname;
} ccalculus;

extern ccalculus compiler;

void argparse(int argc, char** argv);

#endif
