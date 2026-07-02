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

static void out_of_memory(void)
{
    perror(_progname);
    exit(EX_OSERR);
}

static void *check_null(void *p)
{
    if (!p)
        out_of_memory();

    return p;
}

void *xmalloc(size_t size)
{
    return check_null(malloc(size));
}

char *xstrdup(const char *s)
{
    return check_null(strdup(s));
}
