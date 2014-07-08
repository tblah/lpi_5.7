#include <stdlib.h>		// for exit, malloc
#include "bool.h"
#include "errExit.h"
#include "readv.h"
#include "writev.h"
#include "iovec.h"
#include <sys/types.h>	// for open
#include <sys/stat.h>	// for open, lseek
#include <fcntl.h>		// for open
#include <unistd.h>		// for close, unlink, lseek and write
#include <stdio.h>		// for printf

ssize_t useReadv(int fd) {
	struct iovec iov[3];
	short x; 
	int y;
	long int z;
	ssize_t numRead;

	iov[0].iov_base = &x;
	iov[1].iov_base = &y;
	iov[2].iov_base = &z;

	iov[0].iov_len = sizeof(x);
	iov[1].iov_len = sizeof(y);
	iov[2].iov_len = sizeof(z);

	numRead = readv(fd, iov, 3);
	if (numRead == -1)
		errExit("readv");

	return numRead;
}

bool readvTest1() {	// test that when given a file that is 
	int fd = open("file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);	// yeah I know we shouldn't assume that "file" is unique
	if (fd == -1)
		errExit("open");

	// write some junk to the file
	const char buf = 'a';
	size_t numToRead = sizeof(short) + sizeof(int) + sizeof(long int); // number of bytes read by useReadv()

	for (int i = 0; i < (numToRead + 50); i++) {	// 50 extra bytes seems like a nice number
		if (write(fd, &buf, sizeof(buf)) == -1)
			errExit("write");
	}

	if (lseek(fd, 0, SEEK_SET) == -1)
		errExit("lseek");

	if (useReadv(fd) != numToRead) {
		printf("Test 1.0 - Will read in correct amount with a big file \t\t FAILED\n");
		return false;
	}


	close(fd);

	unlink("file");

	printf("Test 1.0 - Will read in correct amount with a big file \t\t PASSED\n");

	return true;
}

bool readvTest2() {
	int fd = open("file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);	// yeah I know we shouldn't assume that "file" is unique
	if (fd == -1)
		errExit("open");

	// write some junk to the file
	const char buf = 'a';

	for (int i = 0; i < sizeof(int); i++) {	// less data than we are going to try to read
		if (write(fd, &buf, sizeof(buf)) == -1)
			errExit("write");
	}

	if (lseek(fd, 0, SEEK_SET) == -1)
		errExit("lseek");

	if (useReadv(fd) != sizeof(int)) {
		printf("Test 1.1 - Will read in correct amount with a small file \t\t FAILED\n");
		return false;
	}


	close(fd);

	unlink("file");

	printf("Test 1.1 - Will read in correct amount with a small file \t PASSED\n");

	return true;
}

bool bothTest3() {
	int fd = open("file", O_RDWR | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);	// yeah I know we shouldn't assume that "file" is unique
	if (fd == -1)
		errExit("open");

	const size_t iovcnt = 1000;
	struct iovec iov[iovcnt];

	// fill with data
	for (int i = 0; i < iovcnt; i++) {
		iov[i].iov_base = malloc(sizeof(int));	// allocate some space
		if (iov[i].iov_base == NULL)
			errExit("malloc");

		*((int*)(iov[i].iov_base)) = i;	// put in some data

		iov[i].iov_len = sizeof(int);
	}


	// write data to file
	if (writev(fd, iov, iovcnt) == -1)
		errExit("writev");

	// clear data in memory buffers
	for (int j = 0; j < iovcnt; j++)
		*((int*)(iov[j].iov_base)) = 0;

	// seek to the beginning of the file
	if (lseek(fd, 0, SEEK_SET) == -1)
		errExit("lseek");

	// read data back in
	if (readv(fd, iov, iovcnt) == -1)
		errExit("readv");

	// verify data
	for (int k = 0; k < iovcnt; k++) {
		if (*((int*)(iov[k].iov_base)) != k) {
			printf("Test 2.0 - Use both \t\t\t\t\t\t FAILED\n");
			return false;
		}
	}

	// free all the memory
	for (int l = 0; l < iovcnt; l++) {
		free(iov[l].iov_base);
	}

	// cleanup
	close(fd);
	unlink("file");

	printf("Test 2.0 - Use both \t\t\t\t\t\t PASSED\n");

	return true;
}

int main(int argc, char* argv[])
{
	if (readvTest1() == false || readvTest2() == false || bothTest3() == false)
		printf("\nSome tests failed :-(\n");
	else
		printf("\nAll tests passed :-)\n");

	exit(EXIT_SUCCESS);
}
