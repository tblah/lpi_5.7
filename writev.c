#include "errExit.h"
#include "iovec.h"
#include <unistd.h>		// for ssize_t and write

ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {
	ssize_t ret = 0;

	for (int i = 0; i < iovcnt; i++) {
		ssize_t numWritten = write(fd, iov[i].iov_base, iov[i].iov_len);
		if (numWritten == -1)
			return -1;

		ret += numWritten;

		if (numWritten < iov[i].iov_len)
			break;	// we cant write any more for whatever reason
	}

	return ret; // placeholder to shut up the error messages
}