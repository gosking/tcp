#include "unp.h"

/*
 *	PAINFULLY SLOW VERSION -- example only.
 */

ssize_t
readline(int fd, void *vptr, size_t maxlen)
{
	char c;
	char *ptr;
	ssize_t n;
	ssize_t rc;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) {	
	/* left last space for null terminate */
	again:
		rc = read(fd, &c, 1);
		if (rc == 1) {
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stored, like fgets()*/
		} else if (rc == 0) {
			*ptr = 0;
			return (n - 1);	/* EOF, n-1 bytes were read */
		} else {
			if (errno == EINTR) /* call read() again */
				goto again;
			return (-1);	/* error, errno set by read()*/
		}
	}
	*ptr = 0;	/* null terminate like fgets()*/
	return (n);
}
