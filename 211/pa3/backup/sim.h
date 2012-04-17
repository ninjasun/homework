#ifndef SIM_H
#define SIM_H

typedef struct node
{
	/*
	 * Struct for each line in the cache.
	 * Contains valid bit, dirty bit, and tag.
	 */
	char vb;
	char db;
	unsigned short tag;
} line;

unsigned int htoi (char *ptr);
	/*
	 * Converts hex to binary
	 */
#endif
