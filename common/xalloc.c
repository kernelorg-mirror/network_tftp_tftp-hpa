/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2026 Intel Corporation; Author: H. Peter Anvin
 */

/*
 * xmalloc.c
 *
 * Simple error-checking version of malloc()
 *
 */

#include "config.h"
#include "tftpsubs.h"

void (*out_of_memory)(void) = NULL;

noreturn static void do_out_of_memory(void)
{
    if (out_of_memory)
        out_of_memory();

    /* If out_of_memory() returns and/or is not set */
    perror(_progname);
    while (1)
        exit(EX_OSERR);
}

static void *check_null(void *p)
{
    if (!p) {
        do_out_of_memory();
    }

    return p;
}

void *xmalloc(size_t size)
{
    /* Use calloc() in the interest of safety */
    return xcalloc(1,size);
}

void *xcalloc(size_t n, size_t size)
{
    if (!n || !size)
        n = size = 1;           /* Avoid undefined behavior 0-byte allocation */
    return check_null(calloc(n,size));
}

void *xrealloc(void *p, size_t newsize)
{
    /* This is paranoia: realloc() is supposed to handle NULL */
    if (!p)
        return xmalloc(newsize);

    return check_null(realloc(p, newsize));
}

char *xstrdup(const char *s)
{
    return check_null(strdup(s));
}

void xfree(void *p)
{
    /* This is paranoia: free() is supposed to handle NULL already */
    if (p)
        free(p);
}
