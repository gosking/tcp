#include "unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE];
	char	recvline[MAXLINE];

	/*	read a line from stdin and send to server.
	 *	a line from server and print out to stdout
	 */
	while (fgets(sendline, MAXLINE, stdin) != NULL) {
		if (writen(sockfd, sendline, MAXLINE) < 0)
			handle_error("writen error")
		if (readline(sockfd, recvline, MAXLINE ) < 0)
			handle_error("readline error");
		if (fputs(recvline, stdout) == EOF)
			handle_error("fputs error");
	}
}
