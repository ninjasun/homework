#include "sim.h"
int main(int argc, char** argv){
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
	for (curr = 0; curr<cSize; curr++){
		cache[curr].vb='0';
	}
	if (argc <=1 || argc >3 || ( (strcmp("wt",argv[1]) != 0) && (strcmp("wb",argv[1]) != 0) ) || (fp=fopen(argv[2],"r"i) == NULL)) 
		return 1;
	policy = ( strcmp("wt",argv[1])==0 ) ? 't' : 'b';
	buffer = malloc(1024);
	memAddress = 0;
	index = 0;
	tagVal = 0;
	blockAddress = 0;
	while (fgets(buffer, 1024, fp) != NULL && buffer[0] !='#') {
		instruction = strstr(buffer, "W") == NULL ? 'r' : 'w';
		memAddress=htoi(buffer)/4;
		index=memAddress%cSize;
		tagVal=memAddress/cSize;
		if (cache[index].vb == '0' || cache[index].tag != tagVal){
			cMiss++;
			memRead++;
			cache[index].tag=tagVal;
			cache[index].vb='1';
		}
		if (policy == 't'){
			if (cache[index].vb=='0' || cache[index].tag!=tagVal)
				cHit++;
			if (instruction == 'w')
				memWrite++;
		}
		else{ /*Write back*/
			if (! (cache[index].vb == '0')){/*No data in index*/
				if (cache[index].tag==tagVal)
					cHit++;
			}
			if (instruction == 'w')
				cache[index].vb='2';
		}
	}
	printf("%s%u\n", "CACHE HITS: ", cHit);
	printf("%s%u\n", "CACHE MISSES: ", cMiss);
	printf("%s%u\n", "MEMORY R (READ): ", memRead);
	printf("%s%u\n", "MEMORY W (WRITE): ", memWrite);
	fclose(fp);
	free(buffer);
	return 0;
}
unsigned int htoi (char *ptr){
	unsigned int value;
	int i,order;
	value=0;
	order = strlen(ptr)-2;
	for(i=order;ptr[i] != 'x'; i--)
		value+= (ptr[i] <= '9' ? ptr[i]-'0' : ptr[i] -'a' + 10)<<((order-i)*4);
	return value;
}
