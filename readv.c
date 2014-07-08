#include "iovec.h"
#include <unistd.h>		// for ssize_t and read

ssize_t readv(int fd, const struct iovec *iov, int iovcnt) {
	ssize_t ret = 0;

	for (int i = 0; i < iovcnt; i++) {
		ssize_t numRead = read(fd, iov[i].iov_base, iov[i].iov_len);
		if (numRead == -1)
			return -1;

		ret += numRead;

		if (numRead < iov[i].iov_len)
			break;
	}

	return ret; // placeholder to shut up the error messages
}