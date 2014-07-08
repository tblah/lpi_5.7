COMPILE_OPTS= -g -Wall -std=c99
COMMON_HEADDERS=errExit.h bool.h
READV_DEPS=readv.c iovec.h
WRITEV_DEPS=$(COMMON_HEADDERS) writev.c iovec.h
TESTER_DEPS=readv.h writev.h iovec.h readv.o writev.o errExit.o $(COMMON_HEADDERS) test.c 

all: tester

test: tester
	./tester

tester: $(TESTER_DEPS)
	cc $(COMPILE_OPTS) -o tester $(TESTER_DEPS)

readv.o: $(READV_DEPS)
	cc $(COMPILE_OPTS) -c -o readv.o readv.c

writev.o: $(WRITEV_DEPS)
	cc $(COMPILE_OPTS) -c -o writev.o writev.c

errExit.o: errExit.c errExit.h
	cc $(COMPILE_OPTS) -c -o errExit.o errExit.c

clean:
	rm tester *.o 
