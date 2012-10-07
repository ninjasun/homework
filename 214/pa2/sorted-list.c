#include "sorted-list.h"


/* Sorted List Functions */
SortedListPtr SLCreate(CompareFuncT cf) {
  SortedListPtr sl = malloc(sizeof(SortedListPtr));

  sl->head = NULL;
  sl->cf = cf;

  return sl;
}



void SLDestroy(SortedListPtr list) {
  free(list->head);
  free(list);

  return;
}




int SLInsert(SortedListPtr list, void *newObj){

  if (newObj == NULL) {
  /* Fail to insert null */
    return 0;
  }

  if (list->head == NULL) {
  /* List is empty */
    Node entry = malloc(sizeof(Node));
    entry->data = newObj;
    entry->next = NULL;
  }
  else {
  /* List has at least 1 element */

  }

  return 1;
}




int SLRemove(SortedListPtr list, void *newObj) {

  return 1;
}





/* Iterator Functions */
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
}




void *SLNextItem(SortedListIteratorPtr iter) {
}
