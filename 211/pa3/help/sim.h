#ifndef SIM_H
#define SIM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
	/*
	 * Struct for each line in the cache.
	 * Contains valid bit, dirty bit, and tag.
	 */
	char db;
	char vb;
	unsigned int tag;
} line;

unsigned int htoi (char *ptr);
	/*
	 * Converts hex to binary
	 */
#endif
