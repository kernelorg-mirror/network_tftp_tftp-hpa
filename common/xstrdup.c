/*
 * xstrdup.c
 *
 * Simple error-checking version of strdup()
 *
 */

#include "config.h"
#include "tftpsubs.h"

char *xstrdup(const char *s)
{
    char *p = strdup(s);

    if (!p) {
        fprintf(stderr, "Out of memory!\n");
        exit(128);
    }

    return p;
}
