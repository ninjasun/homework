#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sim.h"

int main(int argc, char** argv)
{
	unsigned int cHit,cMiss,memRead,memWrite,memAddress,index,blockAddress;
	unsigned short cSize,block,tagVal;
	int curr;
	char policy,instruction;
	line cache[16384];
	FILE *fp;
	char *buffer;
	
	cHit=0;
	cMiss=0;
	memRead=0;
	memWrite=0;

	cSize=16384;
	for (curr = 0; curr<cSize; curr++)
	{
		cache[curr].vb='0';
		cache[curr].db='0';
	}
	block=4;

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
	while (fgets(buffer, 1024, fp)) /*Looping through each line in file*/
	{
		instruction = strstr(buffer, "W") == NULL ? 'r' : 'w';
		memAddress=htoi(buffer);
		blockAddress=memAddress/4;
		index=blockAddress%cSize;
		tagVal=blockAddress/cSize;

		if (policy == 't')
		{
		}
	}


	/*Memory freeing*/
	free(fp);
	free(buffer);
	return 0;
}

unsigned int htoi (char *ptr)
{
	unsigned int sum,power,i,j,val;
	sum = 0;
	power = 0;
	i = strlen(ptr)-1;
	while (ptr[i] != 'x')
	{
		val = (unsigned int)(ptr[i] > 9 ? (ptr[i]+10-'a') : (ptr[i] - '0'));
		for(j=0; j<power;j++)
			val=val*16;
		sum+=val;
		power+=1;
		i-=1;
	}
	return sum;
}
