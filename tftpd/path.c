/*
 * This breaks down a path name into its constituents, removing
 * . and .. components.
 *
 * Returns NULL if the path is invalid (notably if it requires access
 * above the topmost directory level.)
 *
 * To match historical behavior, the path must be absolute, starting
 * with an explicit /.
 *
 * This returns a list of pointers into a string array, all allocated
 * as a single heap allocation.
 */

#include "config.h"
#include "common/tftpsubs.h"
#include "path.h"

/*
 * Validate a filename character. On Unix, disallow ASCII control
 * characters (< 32, 127); on Windows, also disallow \ : and other
 * characters disallowed in file names (use rewrite to translate \
 * into / just as on Unix, if desired.)
 */
static bool is_valid_char(unsigned char c)
{
    switch (c) {
    case 127:
#ifdef _WIN32
    case '<':
    case '>':
    case ':':
    case '"':
    case '\\':                  /* Slashes only for pathname separators! */
    case '|':
    case '?':
    case '*':
#endif
        return false;
    default:
        return c >= ' ';
    }
}

/*
 * Remove components as necessary, return the new tail pointer or NULL.
 */
static const char **adjust_tail(const char **dp, const char **top)
{
    size_t drop = 0;
    const char *last_path = dp[-1];

    if (last_path[0] == '.') {
        if (!last_path[1]) {
            /* . component */
            drop = 1;
        } else if (last_path[1] == '.' && !last_path[2]) {
            /* .. component */
            drop = 2;
        }
    }

    return (dp < top+drop) ? NULL : dp-drop;
}

const char **parse_path(const char *path)
{
    bool was_slash;
    const char *p;
    const char **dirs, **dp;
    char *q;
    size_t path_len;
    size_t ndirs;

    /*
     * For historical reasons, reject the path unless it explicitly
     * beings with a slash.
     */
    if (*path != '/')
        return NULL;            /* Path not absolute */

    /*
     * Allocate space for the dirs list. The *maximum possible* number
     * equals the number of spans of non-slash characters.
     */
    was_slash = true;           /* Implicit leading slash */
    ndirs = 0;
    for (p = path; *p; p++) {
        if (!is_valid_char(*p))
            return NULL;        /* Invalid character in path */
        if (*p == '/') {
            was_slash = true;
        } else if (was_slash) {
            ndirs++;
            was_slash = false;
        }
    }
    path_len = p - path;

    dirs = dp = xmalloc((ndirs+1) * sizeof *dirs + path_len + 1);
    q = (char *)&dirs[ndirs+1];

    was_slash = true;
    while (*q) {
        if (*q == '/') {
            *q = '\0';
            if (!was_slash) {
                dp = adjust_tail(dp, dirs);
                if (!dp)
                    goto fail;
            }
            was_slash = true;
        } else if (was_slash) {
            *dp++ = q;
            was_slash = false;
        }
    }
    if (!was_slash) {
        dp = adjust_tail(dp, dirs);
        if (!dp)
            goto fail;
    }

    return dirs;

fail:
    free(dirs);
    return NULL;
}

/*
 * Construct a canonical form path from a directory list.
 * Returns a newly allocated string.
 */
char *build_path(const char * const *dirs)
{
    size_t size = 1;            /* Space for NUL terminator */
    const char * const *dp;
    char *path, *q;

    for (dp = dirs; *dp; dp++) {
        size_t len = strlen(*dp);
        size += len+1;          /* / + string */
    }

    q = path = xmalloc(size);

    for (dp = dirs; *dp; dp++) {
        size_t len = strlen(*dp);
        *q++ = '/';
        memcpy(q, *dp, len);
        q += len;
    }

    *q = '\0';
    return path;
}

/*
 * Compare two path lists.
 * Returns:
 *  0 on an explicit mismatch
 *  1 if the a is shorter but matches (is a prefix)
 *  2 if the b is shorter but matches (is a prefix)
 *  3 on an exact match
 */
unsigned int compare_paths(const char * const *a, const char * const *b)
{
    while (1) {
        if (!*a) {
            return *b ? 1 : 3;
        } else if (!*b) {
            return 2;
        } else if (strcmp(*a, *b)) {
            return 0;
        }

        a++;
        b++;
    }
}
