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
};

char** buildFiles(const char*);
struct wordnode* buildWordList(const char*);
void andSearch(struct wordnode*, char*);
void orSearch(struct wordnode*, char*);


#endif
