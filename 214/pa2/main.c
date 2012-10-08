/*
 * sorted-list.c
 */

#include	<string.h>
#include	"sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

int main()
{
  SortedListPtr sl = SLCreate(&compareInts);
  
  int* n1 = malloc(sizeof(int*));
  int* n2 = malloc(sizeof(int*));
  int* n3 = malloc(sizeof(int*));
  int* n4 = malloc(sizeof(int*));

  int* n1 = 5;
  int* n2 = 10;
  int* n3 = 3;
  int* n4 = 8;

  SLInsert(sl, n1);
  SLInsert(sl, n2);
  SLInsert(sl, n3);
  SLInsert(sl, n4);

  SortedListIteratorPtr sp = SlCreateIterator(sl);

  void* currentValue = malloc(sizeof(void*));
  currentValue = 0;

  while(currentValue != NULL)
  {
  	currentValue = SLNextItem(sp);
  	printf("%d\n", currentValue);
  }

  
  SLDestroyIteration(sp);
  SLDestroy(sl);
}
