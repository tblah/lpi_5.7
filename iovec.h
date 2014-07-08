#ifndef IOVEC_H
#define IOVEC_H

#include <unistd.h> // ssize_t

struct iovec {
    void  *iov_base;    /* Starting address */
    size_t iov_len;     /* Number of bytes to transfer */
};

#endif