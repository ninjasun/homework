#include "sorted-list.h"


/* Sorted List Functions */
SortedListPtr SLCreate(CompareFuncT cf) {
  SortedListPtr sl = malloc(sizeof(SortedListPtr));

  sl->head = NULL;
  sl->cf = cf;

  return sl;
}



void SLDestroy(SortedListPtr list) {
  Node ptr = list->head;
  while (ptr != NULL) {
    Node current = ptr;
    ptr = ptr->next;
    free(current);
  }

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
    list->head = entry;
  }
  else {
    Node ptr = list->head;

    if (list->cf(list->head->data, newObj) < 0){
    /* New head of list */
      Node entry = malloc(sizeof(Node));
      entry->data = newObj;
      entry->next = ptr;
      list->head = entry;
      return 1;
    }

    /* Insert somewhere in the middle of the list */
    while ( (ptr->next != NULL) && (list->cf(ptr->next->data, newObj) < 0) ) {
      ptr = ptr->next;
    }
    Node entry = malloc(sizeof(Node));
    entry->data = newObj;
    entry->next = ptr->next;
    ptr->next = entry;
  }

  return 1;
}




int SLRemove(SortedListPtr list, void *newObj) {
  if (list->head->data == NULL) {
  /* Empty List */
    return 0;
  }
  else if ( (list->cf(list->head->data, newObj)) == 0) {
  /* Head needs to be removed */
    Node toBeErased = list->head;
    list->head = list->head->next;
    free(toBeErased);

    return 1;
  }
  else {
  /* Need to remove something in the middle */
    Node prev = list->head;
    Node curr = list->head->next;
    if (curr == NULL) {
    /* Edge case bandage */
      return 0;
    }

    while ( (prev->next != NULL) && (list->cf(curr->data, newObj) > 0) ){
      prev = curr;
      curr = curr->next;
    }
    if (list->cf(curr->data, newObj) == 0){
      prev->next = curr->next;
      free(curr);
      return 1;
    }
    else {
      return 0;
    }
  }
}





/* Iterator Functions */
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
  return NULL;
}




void *SLNextItem(SortedListIteratorPtr iter) {
  return NULL;
}
