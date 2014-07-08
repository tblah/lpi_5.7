#ifndef READV_H
#define READV_H

#include <unistd.h>		// for ssize_t
#include "iovec.h"

ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

#endif