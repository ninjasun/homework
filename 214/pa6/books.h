#ifndef BOOK_H
#define BOOK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

struct book {
   char* title;
   double price;
   int customerID;
   char* category;
};

#endif
