#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VAR.h"

int main(int argc, char * argv[])
{
	//checking if the user has given more than 1 variable.
	if(argc!=1)
	{
		Validate(argv);
	}
	else
		printf("\'-h\' or \'--help\' flag for help section\n");
	return 0;
}
