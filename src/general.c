#include <stdint.h>
#include <stdlib.h>

#include "general.h"

Vector new_vector(size_t nmemb, size_t size) {
    return (Vector) {
        .data  = calloc(nmemb, size),
        .peek  = 0,
        .index = 0,
        .size  = size,
    };
}

void free_vector(Vector* vec) {
    free(vec->data);

    vec->data = NULL;
    vec->size = -1;
}
