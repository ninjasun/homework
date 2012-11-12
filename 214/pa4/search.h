#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct filenode {
  char* fileName;
  struct filenode *next;
};

struct wordnode {
  char* word;
  struct wordnode *next;
  struct filenode *files;
};

typedef struct filenode fileNode;
typedef struct wordNode wordNode;

char** buildFiles(const char*);
wordNode* buildWordList(const char*);

#endif
