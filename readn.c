#include "unp.h"
/*
 *	Read "n" bytes from a descriptor.
 */
ssize_t
readn(int fd, void *vptr, size_t n)
{
	/*	
	 *	if konw nleft bytes left in fd,
	 *	then minus nread bytes from the nleft
	 *	and return nleft - nread
	 */
	size_t		nleft;
	ssize_t		nread;
	char *ptr;	/* buff position */
	
	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		nread = read(fd, ptr, nleft);
		if (nread < 0) {
			if (errno == EINTR)
				nread = 0;	/* call readd again */
			else
				return (-1);
		} else if (nread == 0)
			break;	/*	EOF: end of file */

		nleft	-= nread;	/* if nread=0, then nleft no cahaged*/
		ptr		+= nread;
	}
	return (n - nleft);
}
