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
  int* n5 = malloc(sizeof(int*));

  *n1 = 5;
  *n2 = 10;
  *n3 = 3;
  *n4 = 8;
  *n5 = 11;


  printf("Test Case 1: Adding\n");

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

  printf("Test Case 2: Removing \n");

  SortedListIteratorPtr sz = SLCreateIterator(sl);

  SLRemove(sl, n4);
  
  do{
    foo = SLNextItem(sz);
    if (foo == NULL) {
      break;
    }
    printf("%d\n", *foo);
  } while (foo != NULL);

  printf("Test Case 3: Removing/Adding in Middle\n");
  SortedListPtr t3 = SLCreate(&compareInts);

  SLInsert(t3, n1);
  SLInsert(t3, n2);
  SLInsert(t3, n3);
  SLInsert(t3, n4);

  SortedListIteratorPtr p3 = SLCreateIterator(t3);

  foo = SLNextItem(p3);
  printf("%d\n", *foo);
  printf("remove: 8, then continue iterating \n");
  SLRemove(t3, n4);
  printf("add 11, then continue iterating \n");
  SLInsert(t3, n5);
  do{
    foo = SLNextItem(p3);
    if (foo == NULL) {
      break;
    }
    printf("%d\n", *foo);
  } while (foo != NULL);
  printf("Iterate whole list from start \n");
  SortedListIteratorPtr p3a = SLCreateIterator(t3);
  do{
    foo = SLNextItem(p3a);
    if (foo == NULL) {
      break;
    }
    printf("%d\n", *foo);
  } while (foo != NULL);

  printf("Test Case 4: Removing and Iterating Empty List\n");
  SortedListPtr t4 = SLCreate(&compareInts);
  SLRemove(t4, n1);
  SortedListIteratorPtr p4 = SLCreateIterator(t4);
  do{
    foo = SLNextItem(p4);
    if (foo == NULL) {
      break;
    }
    printf("%d\n", *foo);
  } while (foo != NULL);
  

  printf("Test Case 5: Strings\n");
  char* c1 = malloc(sizeof(char) * 5);
  char* c2 = malloc(sizeof(char) * 5);
  char* c3 = malloc(sizeof(char) * 5);
  strcpy(c1, "hey\0");
  strcpy(c2, "yo\0");
  strcpy(c3, "kk\0");

  printf("%s\n", c1);
  SortedListPtr t5 = SLCreate(&compareStrings);
  SLInsert(t5, c1);
  SortedListIteratorPtr p5 = SLCreateIterator(t5);
  char *resp = SLNextItem(p5);
  printf("%s\n", resp);


  free(n1);
  free(n2);
  free(n3);
  free(n4);
  free(n5);
  SLDestroyIterator(p4);
  SLDestroyIterator(p3);
  SLDestroyIterator(p3a);
  SLDestroyIterator(sz);
  SLDestroyIterator(sp);
  SLDestroy(sl);
  SLDestroy(t3);
  SLDestroy(t4);
}
