/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2001-2007 H. Peter Anvin - All Rights Reserved
 *
 *   This program is free software available under the same license
 *   as the "OpenBSD" operating system, distributed at
 *   http://www.openbsd.org/.
 *
 * ----------------------------------------------------------------------- */

/*
 * misc.c
 *
 * Minor help routines.
 */

#include "tftpd.h"

/*
 * Set the signal handler and flags, and error out on failure.
 */
void set_signal(int signum, sighandler_t handler, int flags)
{
    if (tftp_signal(signum, handler, flags)) {
        tftpd_log(LOG_ERR, "sigaction: %m");
        exit(EX_OSERR);
    }
}

/*
 * malloc() that syslogs an error message and bails if it fails.
 * Actually uses calloc() to emphasize safety.
 */
void *tfmalloc(size_t size)
{
    void *p = calloc(1, size);
    if (!p) {
        tftpd_log(LOG_ERR, "calloc: %m");
        exit(EX_OSERR);
    }

    return p;
}

/*
 * realloc() equivalent, which NULL check in case of bugs
 */
void *tfrealloc(void *ptr, size_t size)
{
    void *p;

    if (!ptr)
        p = malloc(size);
    else
        p = realloc(ptr, size);

    if (!p) {
        tftpd_log(LOG_ERR, "realloc: %m");
        exit(EX_OSERR);
    }

    return p;
}

/*
 * strdup() equivalent
 */
char *tfstrdup(const char *str)
{
    char *p = strdup(str);
    if (!p) {
        tftpd_log(LOG_ERR, "strdup: %m");
        exit(EX_OSERR);
    }

    return p;
}

/*
 * free() which explicitly checks for NULL, just in case of bugs
 */
void tffree(void *ptr)
{
    if (ptr)
        free(ptr);
}
