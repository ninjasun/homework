#include <stdio.h>
#include <stdlib.h>

typedef struct word{
   char word[256];
   struct word *next;
   struct file *head;
}word;

typedef struct file{
   char name[256];
   int count;
   struct file *next;
}file;
