#ifndef _UNP_H
#define _UNP_H

#include <stdarg.h>		/* ANSI C header file */
#include <syslog.h>		/* for syslog() */
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define LISTENQ	5
#define MAXLINE 1024
#define SERV_PORT 8888
#define handle_error(msg)	\
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

ssize_t
readn(int fd, void *vptr, size_t n);

ssize_t
writen(int fd, const void *vptr, size_t n);

void
str_cli(FILE *fp, int sockfd);

void
str_echo(int sockfd);

ssize_t
readline(int fd, void *vptr, size_t maxlen);

#endif
