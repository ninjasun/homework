#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fib.h"

int main (int argc, char** argv)
{
	int answer;
	int arg;

	if(argc != 2)
	{
		printf("Invalid number of arguments. Please try again.\n");
		return 1;
	}

	arg = atoi(argv[1]);
	if(arg < 0)
	{
		printf("Invalid input. Please enter a non-negative number and try again.\n");
		return 1;
	}

	if ( strcmp("-h", argv[1]) == 0 )
	{
		printf("Usage: fibonacci <non-negative integer >\n");
		return 0;
	}

	answer = fib(arg);

	if (answer < 0)
		printf ("Overflow\n");
	else
		printf ("%d\n", answer);

	return 0;
}
