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

  *n1 = 5;
  *n2 = 10;
  *n3 = 3;
  *n4 = 8;

  SLInsert(sl, n1);
  SLInsert(sl, n2);
  SLInsert(sl, n3);
  SLInsert(sl, n4);

  SortedListIteratorPtr sp = SLCreateIterator(sl);

  int* foo;
  do{
    foo = SLNextItem(sp);
    if (foo == NULL) {
      break;
    }
    printf("%d\n", *foo);
  } while (foo != NULL);

  SLDestroyIterator(sp);
  SLDestroy(sl);
}
