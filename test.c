#include <stdlib.h>		// for exit
#include "bool.h"
#include "errExit.h"
#include "readv.h"
#include "writev.h"

int main(int argc, char* argv[])
{
	// some junk so that this can link
	if (true == false)
		errExit("I don't understand logic");

	exit(EXIT_SUCCESS);
}
