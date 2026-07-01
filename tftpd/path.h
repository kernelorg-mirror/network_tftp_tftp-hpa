/* SPDX-License-Tag: BSD-3-Clause */
/* Copyright (c) 2026 Intel Corporation; Author: H. Peter Anvin */

#ifndef TFTPD_PATH_H
#define TFTPD_PATH_H 1

const char **parse_path(const char *path);
char *build_path(const char * const *dirs);
unsigned int compare_paths(const char * const *a, const char * const *b);

#endif /* TFTPD_PATH_H */
