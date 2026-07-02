/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2026 Intel Corporation; Author: H. Peter Anvin
 */

#include "config.h"
#include "tftpsubs.h"

const char *_progname;

void set_progname(const char *argv0)
{
    const char *p = strrchr(argv0, '/');
    _progname = p ? p+1 : argv0;
}
