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
	/*	printf("%u\n", memAddress);*/
		index=memAddress%cSize;
		tagVal=memAddress/cSize;
		/*
		blockAddress=memAddress/4;
		index=blockAddress%(cSize/4);
		tagVal=blockAddress/(cSize/4);
		*/

		if (policy == 't')
		{
			if (instruction == 'r')
			{
				if (cache[index].vb == '0')
				{
					cMiss++;
					memRead++;
					cache[index].tag=tagVal;
					cache[index].vb='1';
				}
				else /*Data already in this index*/
				{
					if (tagVal == cache[index].tag)
					{
						/*Tag already exists in cache*/
						cHit++;
					}
					else
					{
						/*Different tag is in cache index*/
						cMiss++;
						memRead++;
						cache[index].tag=tagVal;
					}
				}
			}
			else /*Instruction is write*/
			{
				if(cache[index].vb==0)
				{
					cMiss++;
					memRead++;
					cache[index].vb='1';
					cache[index].tag=tagVal; 
				}
				else 
				{/*Something exists in that index*/
					if (tagVal == cache[index].tag)
					{/*Tag found in cache*/
						cHit++;
					}
					else /*Other tag is in this index*/
					{
						memRead++;
						cMiss++;
						cache[index].tag=tagVal;
					}
				}
				memWrite++;
			}

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
	/*
	unsigned int sum,power,i,j,val;
	sum = 0;
	power = 0;
	i = strlen(ptr)-2;
	while (ptr[i] != 'x')
	{
		val = (ptr[i] > 9 ? (ptr[i]+10-'a') : (ptr[i] - '0'));
		printf("%u\n", val);
		for(j=0; j<power;j++)
			val=val*16;
		sum+=val;
		power+=1;
		i-=1;
	}
	return sum;
	*/
}
