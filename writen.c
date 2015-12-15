#include "unp.h"

/*
 *	Write "n" bytes to a descriptor.
 */
ssize_t
writen(int fd, const void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		nwritten = write(fd, ptr, nleft);
		if (nwritten <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;	/* call write() again */
			else
				return (-1);
		}
		/* normal */
		nleft -= nwritten;	
		ptr += nwritten;
	}
	return (n);
}
