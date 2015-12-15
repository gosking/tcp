#include "unp.h"

int
main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in	servaddr;
	
	if (argc != 2)
		handle_error("usage: tcpcli <IPaddress>");
	
	/*	create a server socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		handle_error("socket error");
	
	/*	connect to server listening socket */
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr) <= 0)
		handle_error("inet_pton error");
	if (connect(sockfd, (struct sockaddr*)&servaddr,
				sizeof(servaddr)) < 0)
		handle_error("connect error");
	printf("client connected success\n");	

	/*	process data from server */
	str_cli(stdin, sockfd);
	
	exit(EXIT_SUCCESS);
}
