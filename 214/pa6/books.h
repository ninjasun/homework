#ifndef BOOK_H
#define BOOK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

struct book {
   char* title;
   double price;
   int id;
   char* category;
   struct book* next;
};

struct customer {
  char* name;
  int id;
  double balance;
  char* address;
  char* state;
  char* zip;
  struct customer* next;
};


struct book* orders = NULL;
struct customer* customerList = NULL;


#endif
