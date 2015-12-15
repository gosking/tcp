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
int daemon_proc;		/* set non-zero for by daemon_init()*/

ssize_t
readn(int fd, void *vptr, size_t n);

ssize_t
writen(int fd, const void *vptr, size_t n);

void
str_cli(FILE *fp, int sockfd);

void
str_echo(int sockfd);

static void err_doit(int, int, const char *, va_list);

/*	Nonfatal error related to system call
 *	Print message and return */

void
err_ret(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, LOG_INFO, fmt, ap);
	va_end(ap);

	return ;
}

/*	Fatal error related to system call
 *	Print message and terminate */

void
err_sys(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	
	exit(EXIT_FAILURE);
}

/*	Fatal error related to system call
 *	Print message, dump core, and terminate */

void
err_dump(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	abort();	/* dump core and terminate */
	
	exit(EXIT_FAILURE);		/* shouldn't get here */
}

/*	Nonfatal error unrelated to system call
 *	Print message and return */

void
err_msg(const char *fmt, ...)
{
	va_list		ap;
	
	va_start(ap, fmt);
	err_doit(0, LOG_INFO, fmt, ap);
	va_end(ap);

	return ;
}

/*	Fatal error unrelated to system call
 *	Print message and terminate */

void
err_quit(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(0, LOG_ERR, fmt, ap);
	va_end(ap);

	exit(EXIT_FAILURE);
}

/*	Print message and return to caller
 *	Caller specifies "errnoflag" and "level" */

static void
err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
	int errno_save;
	int n;
	char buf[MAXLINE + 1];

	errno_save = errno;		/* value caller might want printed*/
	/*	print message from fmt */
#ifdef HAVE_VSNPRINTF
	vsnprintf(buf, MAXLINE, fmt, ap); /* safe */
#else
	vsprintf(buf, fmt, ap);	/* not safe */
#endif
	n = strlen(buf);
	if (errnoflag)
		snprintf(buf + n, MAXLINE - n, ": %s", 
				strerror(errno_save));
	strcat(buf, "\n");

	if (daemon_proc) {
		syslog(level, buf);
	} else {
		fflush(stdout);	/* in case stdout and  stderr are same*/
		fputs(buf, stderr);
		fflush(stderr);
	}

	return ;
}

#endif	/* unp.h */
