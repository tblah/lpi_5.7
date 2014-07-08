COMPILE_OPTS= -g -Wall
GENERAL_DEPS=errExit.o errExit.h bool.h
READV_DEPS=$(GENERAL_DEPS) readv.c iovec.h
WRITEV_DEPS=$(GENERAL_DEPS) writev.c iovec.h
TESTER_DEPS=readv.h writev.h readv.o writev.o $(GENERAL_DEPS) test.c

all: tester

test: tester
	./tester

tester: $(TESTER_DEPS)
	cc $(COMPILE_OPTS) -o tester $(TESTER_DEPS)

readv.o: $(READV_DEPS)
	cc $(COMPILE_OPTS) -c -o readv.o readv.c

writev.o: $(WRITEV_DEPS)
	cc $(COMPILE_OPTS) -c -o writev.o writev.c

# an alias to make me happy (keep the line below with the tab intact)
errExit: errExit.o


errExit.o: errExit.c errExit.h
	cc $(COMPILE_OPTS) -c -o errExit.o errExit.c

clean:
	rm tester *.o
