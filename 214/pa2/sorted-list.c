#include "sorted-list.h"


/* Sorted List Functions */
SortedListPtr SLCreate(CompareFuncT cf) {
  SortedListPtr sl = malloc(sizeof(struct SortedList) + 1);

  sl->head = NULL;
  sl->cf = cf;
  sl->changeCount = 0;

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
  list->changeCount++;

  if (list->head == NULL) {
  /* List is empty */
    Node entry = malloc(sizeof(struct ListElement) + 1);
    entry->data = newObj;
    entry->next = NULL;
    list->head = entry;
  }
  else {
    Node ptr = list->head;

    if (list->cf(list->head->data, newObj) < 0){
    /* New head of list */
      Node entry = malloc(sizeof(struct ListElement) + 1);
      entry->data = newObj;
      entry->next = ptr;
      list->head = entry;
      return 1;
    }

    /* Insert somewhere in the middle of the list */
    while ( (ptr->next != NULL) && (list->cf(ptr->next->data, newObj) > 0) ) {
      ptr = ptr->next;
    }
    Node entry = malloc(sizeof(struct ListElement) + 1);
    entry->data = newObj;
    entry->next = ptr->next;
    ptr->next = entry;
  }

  return 1;
}




int SLRemove(SortedListPtr list, void *newObj) {
  if (list->head == NULL) {
  /* Empty List */
    return 0;
  }
  else if ( (list->cf(list->head->data, newObj)) == 0) {
  /* Head needs to be removed */
    Node toBeErased = list->head;
    list->head = list->head->next;
    free(toBeErased);

    list->changeCount++;
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
      list->changeCount++;
      return 1;
    }
    else {
      return 0;
    }
  }
}



/* Helper Functions */
void reposition (SortedListIteratorPtr iter) {
  Node ptr = iter->list->head;
  if (ptr == iter->ptr){
    return;
  }

  while((ptr != NULL) && (iter->list->cf(ptr->data,iter->maxValue) >= 0)){
    ptr = ptr->next;
  }
  iter->ptr = ptr;

  return;
}




/* Iterator Functions */
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
  SortedListIteratorPtr iter = malloc(sizeof(struct SortedListIterator) + 1);
  iter->list = list;
  iter->ptr = list->head;
  if (iter->ptr == NULL){
    iter->maxValue = NULL;
  }
  else {
    iter->maxValue = list->head->data;
  }
  iter->changeCount = list->changeCount;

  return iter;
}




void SLDestroyIterator(SortedListIteratorPtr iter) {
  free(iter);
  return;
}




void *SLNextItem(SortedListIteratorPtr iter) {
  if (iter->changeCount != iter->list->changeCount) {
    reposition(iter);
  }
  if(iter->ptr == NULL){
    return NULL;
  }
  void* nextItem = iter->ptr->data;
  iter->ptr = iter->ptr->next;
  iter->maxValue = nextItem;

  return nextItem;
}
