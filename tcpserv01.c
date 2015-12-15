#include "unp.h"

int
main(int argc, char **argv)
{
	int		listenfd;
	int		connfd;
	pid_t	childpid;
	socklen_t	clilen;
	struct sockaddr_in cliaddr;
	struct sockaddr_in servaddr;

	/*	create a listen socket */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
		handle_error("socket error");
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	/*	bind listen socket to local(server) address */
	if (bind(listenfd, (struct sockaddr *)&servaddr, 
					sizeof(servaddr)) < 0)
		handle_error("bind error");
	
	/*	turn socket into passive socket */
	if (listen(listenfd, LISTENQ) < 0)
		handle_error("listen error");

	/*	
	 *	accept connection socket 
	 *	from established in listen socket.
	 */
	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = accept(listen, (struct sockaddr *)&cliaddr,
								&clilen);
		if (connfd < 0)
			handle_error("accept error");

	/*	create child process by call fork() */
		childpid = fork();
		if (childpid < 0)
			handle_error("fork error");
		else if (childpid == 0) {
			if (close(listenfd) < 0)/* close listening socket*/
				handle_error("child:close listenfd error");
			str_echo(connfd);	/* process the request */
			exit(EXIT_SUCCESS);
		}
		if (close(connfd) < 0)/*parent close connected socket*/
			handle_error("parent:close connfd error");
	}
}
