#ifndef WRITEV_H
#define WRITEV_H

#include <unistd.h>		// for ssize_t
#include "iovec.h"

ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#endif