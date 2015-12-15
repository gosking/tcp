#include "unp.h"

void
str_echo(int sockfd)
{
	ssize_t	n;
	char	buf[MAXLINE];

	while ( (n = readline(sockfd, buf, MAXLINE)) > 0) {
		if (writen(sockfd, buf, n) < 0)
			handle_error("writen error");
	}
		/*	error handling */
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		handle_error("str_echo:read error");
}
