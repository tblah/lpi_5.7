#include "errExit.h"
#include "iovec.h"
#include <unistd.h>		// for ssize_t

ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {

	return 0; // placeholder to shut up the error messages
}