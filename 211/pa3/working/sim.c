#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sim.h"

int main(int argc, char** argv)
{
	unsigned int cHit,cMiss,memRead,memWrite,memAddress,index,blockAddress,tagVal;
	unsigned short cSize;
	int curr;
	char policy,instruction;
	line cache[4096];
	FILE *fp;
	char *buffer;
	
	cHit=0;
	cMiss=0;
	memRead=0;
	memWrite=0;

	cSize=4096;
	for (curr = 0; curr<cSize; curr++)
	{
		cache[curr].vb='0';
		cache[curr].db='0';
	}

	/*Checking for valid arguments*/
	if (argc <=1 || argc >3)
	{
		printf("Invalid input. Please run again\n");
		return 1;
	} 
	/*Checking for -h option*/
	if ( strcmp( "-h", argv[1] ) == 0 )
	{
		printf("Usage: sim <write policy> <trace file>");
		return 0;
	}

	/*Checking for valid write policy*/
	if ( (strcmp("wt",argv[1]) != 0) && (strcmp("wb",argv[1]) != 0) )
	{
		printf("Invalid write policy. Please run again.");
		return 1;
	}

	/*Setting policy*/
	if ( strcmp("wt",argv[1])==0 )
		policy='t'; /*Set policy to write-through*/
	else
		policy='b'; /*Set policy to write-back*/
	
	/*Opening trace file*/
	fp = fopen(argv[2],"r");

	/*Checking if trace file is found*/
	if (fp == NULL)
	{
		printf("Trace file not found. Please run again.");
		return 1;
	}

	buffer = malloc(1024);
	memAddress = 0;
	index = 0;
	tagVal = 0;
	blockAddress = 0;
	while (fgets(buffer, 1024, fp) != NULL && buffer[0] !='#') /*Looping through each line in file*/
	{
		instruction = strstr(buffer, "W") == NULL ? 'r' : 'w';
		memAddress=htoi(buffer);
		memAddress=memAddress/4;
		index=memAddress%cSize;
		tagVal=memAddress/cSize;

		if (policy == 't')/*Write through*/
		{
			if (cache[index].vb == '0')/*No data in index*/
			{
				cMiss++;
				memRead++;
				cache[index].tag=tagVal;
				cache[index].vb='1';
			}
			else /*Data already in this index*/
			{
				if (tagVal == cache[index].tag) /*Tag already exists in cache*/
					cHit++;
				else
				{
					/*Different tag is in cache index*/
					cMiss++;
					memRead++;
					cache[index].tag=tagVal;
				}
			}
			if (instruction == 'w')
				memWrite++;
		}
		else /*Write back*/
		{
			if (cache[index].vb == '0')/*No data in index*/
			{
				cMiss++;
				memRead++;
				cache[index].tag=tagVal;
				cache[index].vb='1';
			}
			else /*Data already is in this index*/
			{
				if (cache[index].tag==tagVal) /*Tag is already in the cache*/
					cHit++;
				else /*Different tag is in the cache*/
				{
					if (cache[index].db == '1')
						memWrite++;

					cache[index].tag=tagVal;
					cache[index].db='0';
					cMiss++;
					memRead++;
				}
			}

			if (instruction == 'w')
				cache[index].db='1';
		}
	}
	
	/*Printing output*/
	printf("%s%u\n", "CACHE HITS: ", cHit);
	printf("%s%u\n", "CACHE MISSES: ", cMiss);
	printf("%s%u\n", "MEMORY R (READ): ", memRead);
	printf("%s%u\n", "MEMORY W (WRITE): ", memWrite);
	
	/*Memory freeing*/
	fclose(fp);
	free(buffer);
	return 0;
}

unsigned int htoi (char *ptr)
{
	unsigned int value;
	int i,order;
	value=0;
	order = strlen(ptr)-2;
	for(i=order;ptr[i] != 'x'; i--)
		value+= (ptr[i] <= '9' ? ptr[i]-'0' : ptr[i] -'a' + 10)<<((order-i)*4);
	return value;
}
