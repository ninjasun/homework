#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct filenode {
  char* word;
  fileNode* next;
} fileNode;

typedef struct wordnode {
  char* word;
  wordNode* next;
} wordNode;

char** buildFiles(const char*);
file** buildWordList(const char*);

#endif
