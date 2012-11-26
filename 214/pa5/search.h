#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct filenode {
  char* fileName;
  struct filenode* next;
};

struct wordnode {
  char* word;
  struct wordnode* next;
  struct filenode* files;
  unsigned int size;
};

char** buildFiles(const char*, unsigned int);
struct wordnode* buildWordList(const char*);
void andSearch(struct wordnode*, char*);
void orSearch(struct wordnode*, char*);


#endif
