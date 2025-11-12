/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2001-2025 H. Peter Anvin - All Rights Reserved
 *
 *   This program is free software available under the same license
 *   as the "OpenBSD" operating system, distributed at
 *   http://www.openbsd.org/.
 *
 * ----------------------------------------------------------------------- */

/*
 * recvfrom.h
 *
 * Header for recvfrom substitute and socket configuration functions
 */

#include "config.h"

int
myrecvfrom(int s, void *buf, int len, unsigned int flags,
           union sock_addr *from, union sock_addr *myaddr);
void tftpd_config_socket(int fd, int peer);
void set_socket_nonblock(int fd, int flag);

/* On Cygwin, a nonblocking socket can cause immediate return from select?! */
#ifdef __CYGWIN__
#define cygwin_set_socket_nonblock(fd,flag) set_socket_nonblock(fd,flag)
#else
#define cygwin_set_socket_nonblock(fd,flag) ((void)0)
#endif
