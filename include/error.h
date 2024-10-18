#ifndef ERROR_H
#define ERROR_H

#define WARN_USAGE()               fprintf(stderr, "usage: thicc -s [source] -o [out]\n");
#define WARN_NOT_IMPLEMENTED(msg)  fprintf(stderr, "WARN: " msg " not yet implemented\n");

#endif